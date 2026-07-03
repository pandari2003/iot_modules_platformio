#ifndef HTMLPAGE_H
#define HTMLPAGE_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Mobile LED Control</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <style>
        html {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
            background-color: #f4f7f6;
            color: #333;
            text-align: center;
        }

        body {
            max-width: 400px;
            margin: 0 auto;
            padding: 20px;
        }

        h2 {
            font-size: 2.2rem;
            margin-top: 30px;
            color: #2c3e50;
        }

        p {
            font-size: 1.1rem;
            color: #7f8c8d;
            margin-bottom: 40px;
        }

        .btn {
            display: block;
            width: 100%;
            box-sizing: border-box;
            border: none;
            color: white;
            padding: 20px;
            font-size: 24px;
            font-weight: bold;
            margin: 15px 0;
            cursor: pointer;
            border-radius: 12px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.1);
        }

        .btn-on {
            background: #2ecc71;
        }

        .btn-off {
            background: #e74c3c;
        }
    </style>
</head>

<body>

<h2>ESP32 Controller</h2>
<p>Tap a button below to control the LED</p>

<button class="btn btn-on" onclick="toggleLED('on')">TURN ON</button>
<button class="btn btn-off" onclick="toggleLED('off')">TURN OFF</button>

<script>
function toggleLED(state)
{
    fetch('/led/' + state)
    .then(response => console.log(state))
    .catch(err => console.log(err));
}
</script>

</body>
</html>
)rawliteral";

#endif