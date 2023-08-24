const char* htmlPage = R"(
<html><head>
<meta charset='UTF-8'>
<meta name='viewport' content='width=device-width, initial-scale=1.0'>
<style>
body { background-color: #1d1f21; font-family: 'Hack', monospace; color: #c5c8c6; text-align: center; margin: 0; padding: 0; }
.buttons { display: flex; justify-content: center; align-items: center; height: 100vh; }
.button-group { display: flex; flex-direction: column; align-items: center; }
.button-row { display: flex; }
.button { margin: 5px; }
.button input[type='button'] { display: block; padding: 15px 25px; background-color: #4e9a06; color: #ffffff; border: none; border-radius: 50%; cursor: pointer; box-shadow: 0 0 10px rgba(0, 0, 0, 0.3); font-size: 16px; }
@media (max-width: 768px) {
  .button input[type='button'] { padding: 30px 50px; font-size: 20px; }
}
</style>
<link href='https://fonts.googleapis.com/css?family=Hack' rel='stylesheet'>
</head><body>
<h1>Интерфейс управления роботом Художником</h1>
<div class='buttons'>
  <div class='button-group'>
    <div class='button-row'>
      <div class='button'><input type='button' value='↖' onmousedown='startSending(5)' onmouseup='stopSending(9)' ontouchstart='startSending(8)' ontouchend='stopSending(9)'></div>
      <div class='button'><input type='button' value='↑' onmousedown='startSending(1)' onmouseup='stopSending(9)' ontouchstart='startSending(2)' ontouchend='stopSending(9)'></div>
      <div class='button'><input type='button' value='↗' onmousedown='startSending(6)' onmouseup='stopSending(9)' ontouchstart='startSending(9)' ontouchend='stopSending(9)'></div>
    </div>
    <div class='button-row'>
      <div class='button'><input type='button' value='←' onmousedown='startSending(2)' onmouseup='stopSending(9)' ontouchstart='startSending(4)' ontouchend='stopSending(9)'></div>
      <div class='button'><input type='button' value='○' onmousedown='startSending(9)' onmouseup='stopSending(9)' ontouchstart='startSending(0)' ontouchend='stopSending(9)'></div>
      <div class='button'><input type='button' value='→' onmousedown='startSending(3)' onmouseup='stopSending(9)' ontouchstart='startSending(6)' ontouchend='stopSending(9)'></div>
    </div>
    <div class='button-row'>
      <div class='button'><input type='button' value='↙' onmousedown='startSending(7)' onmouseup='stopSending(9)' ontouchstart='startSending(7)' ontouchend='stopSending(9)'></div>
      <div class='button'><input type='button' value='↓' onmousedown='startSending(4)' onmouseup='stopSending(9)' ontouchstart='startSending(3)' ontouchend='stopSending(9)'></div>
      <div class='button'><input type='button' value='↘' onmousedown='startSending(8)' onmouseup='stopSending(9)' ontouchstart='startSending(5)' ontouchend='stopSending(9)'></div>
    </div>
  </div>
</div>
<script>
var socket = new WebSocket('ws://' + location.hostname + ':81/');
var interval;

function startSending(command) {
  interval = setInterval(function() {
    socket.send(command.toString());
  }, 10); // Отправляем каждые 10 миллисекунд
}

function stopSending(command) {
  clearInterval(interval);
  socket.send(command.toString());
}
</script>
</body></html>
)";
