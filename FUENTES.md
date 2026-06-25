Uso de Inteligencia Artificial,
Código receptor ESP-NOW + Telegram (firmware/receptor_telegram.ino),
Herramienta: Claude Sonnet (Anthropic, junio 2026),
Prompt utilizado: "ayúdame a crear un código para ESP32 receptor ESP-NOW que cuando 
reciba una señal de humo del sensor MQ-2, mande una alerta por Telegram 
en vez de solo encender un LED",
Adaptación: Se configuró con nuestro token de bot (@se_quema_todo_bot), 
nuestro Chat ID personal, y se ajustó la lógica de la bandera 
alertaYaEnviada para que solo envíe UN mensaje por evento de humo y 
se resetee cuando el sensor deje de detectar humo.,
Comprensión: El equipo entiende que el código usa ESP-NOW para recibir 
datos del emisor MQ-2, pausa ESP-NOW temporalmente para conectarse al 
WiFi y enviar el mensaje por HTTPS a la API de Telegram, y luego restaura 
ESP-NOW para seguir escuchando. La bandera volatile bool hayAlerta actúa 
como puente entre el callback de interrupción y el loop principal.
