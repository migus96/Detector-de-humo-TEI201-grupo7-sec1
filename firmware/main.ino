// ============================================================
// RECEPTOR ESP-NOW + ALERTA POR TELEGRAM
// Solo manda UN mensaje por evento de humo
// ============================================================

#include <esp_now.h>           // librería para comunicación ESP-NOW entre ESP32
#include <WiFi.h>              // librería WiFi del ESP32
#include <esp_wifi.h>          // librería para configurar canal WiFi manualmente
#include <WiFiClientSecure.h>  // cliente HTTPS con soporte SSL (necesario para Telegram)
#include <UniversalTelegramBot.h> // librería del bot de Telegram

// ── CAMBIA SOLO ESTAS DOS LÍNEAS ──────────────────────────
const char* ssid     = "TU_WIFI";       // nombre de tu red WiFi
const char* password = "TU_CONTRASEÑA"; // contraseña de tu red WiFi

// ── Datos de tu bot (ya configurados) ─────────────────────
#define BOT_TOKEN  "8135366053:AAF9Hfi9prI0F2iwFns8lKCEzgbfaYCiG0M" // token de @BotFather
#define CHAT_ID    "5567512625"          // tu Chat ID de @userinfobot

// ── Pin del LED ───────────────────────────────────────────
int ledPin = 2;                          // LED integrado del ESP32

// ── Variables de control ──────────────────────────────────
volatile bool hayAlerta      = false;   // true = hay que mandar mensaje a Telegram
                                        // volatile porque se modifica en el callback ESP-NOW
bool          alertaYaEnviada = false;  // true = ya se mandó el mensaje, no reenviar
                                        // se resetea solo cuando el humo desaparece

// ── Objetos para Telegram ─────────────────────────────────
WiFiClientSecure clienteSeguro;         // cliente con SSL para conectar a Telegram de forma segura
UniversalTelegramBot bot(BOT_TOKEN, clienteSeguro); // instancia del bot con tu token

// ============================================================
// CALLBACK ESP-NOW
// Se ejecuta automáticamente cada vez que llega un dato del MQ-2
// ============================================================
void OnDataRecv(const esp_now_recv_info_t * info, const uint8_t *incomingData, int len) {
  bool alerta;                           // variable temporal para guardar el dato recibido
  memcpy(&alerta, incomingData, sizeof(alerta)); // copia los bytes recibidos a la variable

  if (alerta) {                          // si el MQ-2 detectó humo
    digitalWrite(ledPin, HIGH);          // enciende el LED
    Serial.println("******************************************");
    Serial.println("!!! SEÑAL RECIBIDA: ALERTA DE HUMO !!!");
    Serial.println("******************************************");

    if (!alertaYaEnviada) {             // solo activa si NO se había mandado ya el mensaje
      hayAlerta = true;                 // le avisa al loop() que mande el Telegram
    }
    // si alertaYaEnviada es true, no hace nada → evita el spam de mensajes

  } else {                              // si el MQ-2 ya no detecta humo
    digitalWrite(ledPin, LOW);          // apaga el LED
    hayAlerta        = false;           // cancela cualquier envío pendiente
    alertaYaEnviada  = false;           // resetea el bloqueo → permite nueva alerta
    Serial.println("[Sensor] Humo despejado, listo para nueva alerta");
  }
}

// ============================================================
// ENVIAR TELEGRAM
// Pausa ESP-NOW, conecta al WiFi, manda el mensaje, restaura ESP-NOW
// ============================================================
void enviarTelegram(String mensaje) {
  Serial.println("[Telegram] Conectando al WiFi...");

  esp_now_deinit();                     // pausa ESP-NOW para liberar el WiFi

  WiFi.begin(ssid, password);           // inicia conexión WiFi con tus credenciales
  unsigned long inicio = millis();      // guarda el tiempo de inicio para el timeout

  // espera hasta 10 segundos a que conecte
  while (WiFi.status() != WL_CONNECTED && millis() - inicio < 10000) {
    delay(300);                         // espera 300ms entre cada intento
    Serial.print(".");                  // muestra progreso en el Monitor Serial
  }

  if (WiFi.status() != WL_CONNECTED) { // si pasaron 10 segundos sin conectar
    Serial.println("\n[Telegram] Sin WiFi, no se pudo enviar");
  } else {                              // si conectó exitosamente
    Serial.println("\n[Telegram] Conectado! Enviando...");
    clienteSeguro.setInsecure();        // acepta el certificado SSL de Telegram sin verificar
    bool ok = bot.sendMessage(CHAT_ID, mensaje, "Markdown"); // envía el mensaje
    if (ok) Serial.println("[Telegram] ✓ Mensaje enviado!"); // confirmación de éxito
    else    Serial.println("[Telegram] ✗ Error al enviar");  // error en el envío
  }

  WiFi.disconnect();                    // desconecta del WiFi
  delay(100);                           // pausa para que el WiFi se desconecte limpiamente
  WiFi.mode(WIFI_STA);                  // vuelve a modo estación
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // restaura el canal 1 de ESP-NOW
  esp_now_init();                       // reinicia ESP-NOW
  esp_now_register_recv_cb(OnDataRecv); // vuelve a registrar el callback
  Serial.println("[ESP-NOW] Restaurado, escuchando de nuevo...");
}

// ============================================================
// SETUP — se ejecuta una sola vez al encender el ESP32
// ============================================================
void setup() {
  Serial.begin(115200);                 // inicia comunicación serial a 115200 baudios

  WiFi.mode(WIFI_STA);                  // modo estación (cliente), no punto de acceso
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // canal 1, igual que el emisor MQ-2

  pinMode(ledPin, OUTPUT);              // configura el pin del LED como salida
  digitalWrite(ledPin, LOW);            // LED apagado al inicio

  if (esp_now_init() != ESP_OK) {       // intenta iniciar ESP-NOW
    Serial.println("Error inicializando ESP-NOW"); // si falla muestra error
    return;                             // sale del setup sin continuar
  }

  esp_now_register_recv_cb(OnDataRecv); // registra la función que se llama al recibir datos

  Serial.println("RECEPTOR LISTO EN CANAL 1");
  Serial.println("Esperando señal inalámbrica del sensor...");
}

// ============================================================
// LOOP — se repite constantemente
// ============================================================
void loop() {
  if (hayAlerta) {                      // si el callback activó la bandera de alerta
    hayAlerta        = false;           // resetea la bandera inmediatamente
    alertaYaEnviada  = true;            // bloquea nuevos envíos hasta que el humo se despeje

    // construye el mensaje con formato Markdown para Telegram
    String msg = "";
    msg += "🔥 *¡ALERTA DE HUMO!*\n";
    msg += "──────────────────\n";
    msg += "⚠️ El sensor MQ-2 detectó humo\n";
    msg += "⏱ Tiempo activo: `" + String(millis()/1000) + " seg`"; // segundos desde que encendió

    enviarTelegram(msg);                // llama a la función que conecta y manda el mensaje
  }
}
