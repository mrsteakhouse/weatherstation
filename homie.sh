# Base
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/$homie' -m '4.0'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/$name' -m 'Living Room Temperature'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/$state' -m 'ready'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/$nodes' -m 'temperature,pump'

# Air Quality data
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/$name' -m 'Temperature'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/$properties' -m 'temp,hum,p'

# Temperature
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/temp' -m '0'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/temp/$name' -m 'Temperature'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/temp/$unit' -m '°C'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/temp/$datatype' -m 'integer'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/temp/$settable' -m 'false'

# Humidity
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/hum' -m '0'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/hum/$name' -m 'Humidity'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/hum/$unit' -m '%'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/hum/$datatype' -m 'integer'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/hum/$settable' -m 'false'

# Pressure
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/p' -m '0'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/p/$name' -m 'Air Pressure'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/p/$unit' -m 'hPa'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/p/$datatype' -m 'integer'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/temperature/p/$settable' -m 'false'

#  Pump pressure state
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/pump/$name' -m 'Pump state'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/pump/$properties' -m 'alarm'

# Pump okay boolean
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/pump/alarm' -m '1'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/pump/alarm/$name' -m 'Pump okay'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/pump/alarm/$unit' -m ''
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/pump/alarm/$datatype' -m 'boolean'
mosquitto_pub -r -h 192.168.0.59 -t 'homie/living-room-temp/pump/alarm/$settable' -m 'false'