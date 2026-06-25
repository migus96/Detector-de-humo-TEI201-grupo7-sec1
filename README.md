# Detector-de-humo-TEI201-grupo7-sec1
## Descripción del Proyecto
Sistema de seguridad inteligente para la detección de incendios basado en tecnología IoT. El sistema utiliza dos placas ESP32, un sensor MQ-2, shield y batería recargable para monitorear la calidad del aire y detectar niveles de humo, enviando notificaciones de alerta en tiempo real a través de un Bot de Telegram que el usuario puede recibir en su celular.


## EQUIPO
|         Integrante        |    Rol               | GitHub      |
|---------------------------|----------------------|-------------|
|  Benjamín Núñez           | Software/Firmware    | benja090605 |
|  Benjamín Landsberger     | Presentacion/GitHub  | Lacope3488  |
|  Miguel Sánchez           | Diseño 3D/ GitHub    |  migus96    |

## Descripción del problema
El principal problema que tuvimos en el Avance 1 fue que nuestra idea de proyecto si bien no estaba mal formulada, era muy dificil de llevar a cabo y desarrollar de manera correcta a lo largo del curso, debido a la complejidad de su posible solución. Decidimos que era mejor cambiar de perspectiva y desarrollar nuestro proyecto actual, el detector de humo que alerta al usuario en caso de detectar indicios de un posible incendio, esto es gracias al sensor MQ-2 que tiene incorporado y a una alerta que transmite via Telegram.

## Características Principales
Detección Inalámbrica: Comunicación de bajo consumo entre la unidad emisora y la unidad receptora (placas ESP32).
Alerta en Tiempo Real: Notificaciones luego de un corto periodo de tiempo recibidas en el celular mediante la aplicación de Telegram.
Encapsulado: Carcasa impresa en 3D diseñada para proteger los componentes críticos.

## Tecnologías Utilizadas
Hardware: 2x placa ESP32 , Sensor MQ-2, Shield, Batería recargable.
Firmware: C++ (Arduino IDE) con protocolo ESP-NOW.
Diseño: Autodesk Fusion 360 para modelado y planos.
Integración: Bot de Telegram.


## Arquitectura del sistema 

Sensor MQ-2 -> ESP32 Emisora -> Conexión inalámbrica -> ESP32 Receptora -> Bot de Telegram -> Notificación en bandeja de mensajes de Telegram del usuario
