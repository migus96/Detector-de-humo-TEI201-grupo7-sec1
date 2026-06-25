| Librería | Versión | Uso en el proyecto | Fuente |
| :--- | :--- | :--- | :--- |
| UniversalTelegramBot | 1.3.0 | Control y envío de alertas a Telegram | github.com/witnessmenow/Universal-Arduino-Telegram-Bot |
| ArduinoJson | 7.4.3 | Parseo de datos JSON | github.com/bblanchon/ArduinoJson |
| WiFi | Integrada | Conexión WiFi | Espressif (Core ESP32) |
| WiFiClientSecure | Integrada | Conexión segura HTTPS | Espressif (Core ESP32) |


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
