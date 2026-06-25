Librerías utilizadas
| Librería | Versión | Uso en el proyecto | Fuente |
| :--- | :--- | :--- | :--- |
| esp_now.h | Integrada | Comunicación inalámbrica entre placas | Core ESP32 |
| WiFi.h | Integrada | Conexión a red WiFi | Core ESP32 |
| esp_wifi.h | Integrada | Configuración manual de canales WiFi | Core ESP32 |
| WiFiClientSecure.h | Integrada | Conexión HTTPS segura para Telegram | Core ESP32 |
| UniversalTelegramBot.h | 1.3.0 | Control y envío de alertas al Bot de Telegram | github.com/witnessmenow |
| ArduinoJson.h | 7.4.3 | Parseo de respuestas y datos en formato JSON | github.com/bblanchon |
| NewPing.h | 1.9.7 | Gestión y control de sensores | github.com/thomasfredericks |


##Uso de Inteligencia Artificial

##Código receptor ESP-NOW + Telegram (firmware/receptor_telegram.ino),
-  Herramienta: Claude Sonnet (Anthropic, junio 2026),
-  Prompt utilizado: "ayúdame a crear un código para ESP32 receptor ESP-NOW que cuando reciba una señal de humo del sensor MQ-2, mande una alerta por Telegram en vez de solo encender un LED",
-  Adaptación: Se configuró con nuestro token de bot (@se_quema_todo_bot), nuestro Chat ID personal, y se ajustó la lógica de la bandera alertaYaEnviada para que solo envíe UN mensaje por evento de humo y se resetee cuando el sensor deje de detectar humo.
-  Comprensión: El equipo entiende que el código usa ESP-NOW para recibir datos del emisor MQ-2, pausa ESP-NOW temporalmente para conectarse al WiFi y enviar el mensaje por HTTPS a la API de Telegram, y luego restaura ESP-NOW para seguir escuchando.
   La bandera volatile bool hayAlerta actúa como puente entre el callback de interrupción y el loop principal.

   ##Código externo adaptado
Estructura de Bot de Telegram (receptor_telegram.ino)
Fuente: Ejemplos oficiales de UniversalTelegramBot (ej. FlashLed).
Adaptación: Se eliminó la lógica de control de LED y se reemplazó por la recepción de señales vía ESP-NOW, integrando la lógica para validar el Chat ID y enviar alertas de humo específicas.

## Declaración IA Apoyo Diseño de la Carcasa y Planos Técnicos en Fusion 360
Herramienta: Gemini (Google, junio 2026).
Uso/Prompt: Apoyo en la generación de planos técnicos y renders del encapsulado. Se utilizó de forma ocasional para consultar funciones específicas de Fusion 360 y solicitar consejos sobre cómo realizar acciones de modelado o configurar la exportación de planos que no sabía ejecutar por cuenta propia.
Adaptación: El equipo utilizó las indicaciones para configurar correctamente la escala y las vistas de los planos técnicos, organizar la presentación de los renders exportados y resolver dudas sobre el flujo de trabajo dentro de Fusion 360 para cumplir con los entregables del avance.
