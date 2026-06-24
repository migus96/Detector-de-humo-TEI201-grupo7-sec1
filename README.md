# Detector-de-humo-TEI201-grupo7-sec1
Nuestro sistema integra un sensor MQ-2, Shield, batería recargable y una ESP32, se enfoca en prevenir o detectar posibles inicios de incendios en zonas poco concurridas, alerta al usuario en caso de detectar humo propagándose en el entorno.
## EQUIPO
|         Integrante        |    Rol               | GitHub      |
|---------------------------|----------------------|-------------|
|  Benjamín Núñez           | Software/Firmware    |             |
|  Benjamín Landsberger     | Hardware/GitHub      |             |
|  Miguel Sánchez           | Diseño 3D/ GitHub    |  migus96    |

## Descripción del problema
El principal problema que tuvimos en el Avance 1 fue que nuestra idea de proyecto si bien no estaba mal formulada, era muy dificil de llevar a cabo y desarrollar de manera correcta a lo largo del curso, debido a la complejidad de su posible solución. Decidimos que era mejor cambiar de perspectiva y desarrollar nuestro proyecto actual, el detector de humo que alerta al usuario en caso de detectar indicios de un posible incendio, esto es gracias al sensor MQ-2 que tiene incorporado y a una alerta que transmite via Telegram.

## Arquitectura del sistema 

Sensor MQ-2 -> ESP32 Emisora -> Conexión inalámbrica -> ESP32 Receptora -> Bot de Telegram -> Notificación en bandeja de mensajes de Telegram del usuario
