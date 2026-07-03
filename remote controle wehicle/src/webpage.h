#ifndef WEBPAGE_H
#define WEBPAGE_H

const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>

<html>

<head>

<meta name="viewport" content="width=device-width, initial-scale=1">

<style>

body{

font-family:Arial;

text-align:center;

background:#f2f2f2;

}

button{

width:140px;

height:70px;

font-size:22px;

margin:10px;

border:none;

border-radius:10px;

background:#2196F3;

color:white;

}

.stop{

background:red;

}

</style>

</head>

<body>

<h2>ESP32 WiFi Car</h2>

<button onclick="send('forward')">Forward</button><br>

<button onclick="send('left')">Left</button>

<button class="stop" onclick="send('stop')">Stop</button>

<button onclick="send('right')">Right</button><br>

<button onclick="send('backward')">Backward</button>

<script>

function send(cmd)
{
fetch("/"+cmd);
}

</script>

</body>

</html>

)rawliteral";

#endif