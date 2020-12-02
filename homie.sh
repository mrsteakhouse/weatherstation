#!/bin/bash

HOST=192.168.0.59
# Base
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/$homie' -m '4.0'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/$name' -m 'Wintergarten Temperature'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/$state' -m 'ready'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/$nodes' -m 'temperature,pump'

# Air Quality data
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/$name' -m 'Temperature'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/$properties' -m 'temp,hum,p,bat'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/$meta/wot/$value' -m 'TemperatureSensor,HumiditySensor,BarometricPressureSensor'

# Temperature
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/temp' -m '0'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/temp/$name' -m 'Temperature'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/temp/$unit' -m '°C'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/temp/$datatype' -m 'float'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/temp/$settable' -m 'false'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/temp/$meta/wot/$value' -m 'TemperatureProperty'

# Humidity
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/hum' -m '0'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/hum/$name' -m 'Humidity'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/hum/$unit' -m '%'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/hum/$datatype' -m 'float'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/hum/$settable' -m 'false'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/hum/$meta/wot/$value' -m 'HumidityProperty'

# Pressure
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/p' -m '0'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/p/$name' -m 'Air Pressure'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/p/$unit' -m 'hPa'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/p/$datatype' -m 'float'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/p/$settable' -m 'false'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/p/$meta/wot/$value' -m 'BarometricPressureProperty'

# Battery
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/bat' -m '0'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/bat/$name' -m 'Battery'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/bat/$unit' -m 'V'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/bat/$datatype' -m 'float'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/bat/$settable' -m 'false'
mosquitto_pub -r -h $HOST -t 'homie/wintergarten/temperature/bat/$meta/wot/$value' -m 'VoltageProperty'