This project is a for streaming Analog data read from anlog pin of NodeMcu 8266 wifi shield using nodejs. The nodemcu has only
one analog pin so it's extended to 8 channels using Multiplexer. 

Hardware Requirements -
* Node Mcu 8266 Module with wifi inbuilt
* Jumper wires, bread board, Multiplexer (incase you want to extend to multiple analog pin)
   (if you just want to stick to one analog pin then it's not necessary)

Software Requirements
- Nodejs as server that can accept http request and ping back to multiple listening devices using socket
   (package.json is provided -  run npm install after cd into it)
- Bit of Lua code to stream the read signals from analog pin to http post 
- Dont forget to flash with NODEMCU FLasher before pushing the code to NODEMCU
- Arduino Ide (Installed with NODEMCU esp 8266 Library installed from preferences tab in file menu, google for more.. )
- Push the code to Nodemcu, run server to listen requests, open browser and visit the address specified in nodejs code
    - http://localhost:5000 
                  ** Port can be configured by yourself
