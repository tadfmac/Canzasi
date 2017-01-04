var MINI = require('minified');
var _=MINI._, $=MINI.$, $$=MINI.$$, EE=MINI.EE, HTML=MINI.HTML;

$(function() {

navigator.requestI2CAccess().then((i2cAccess) => {
  var port = i2cAccess.ports.get(0);
  var value = [0,0,0,0];
  var valueOld = [0,0,0,0];
  var analog = new canzasi(port);
  var registerNumber = 0;
  analog.init().then(() => {
    console.log("analog.init() done!");
    setInterval(() => {
      analog.get(0x10+registerNumber).then((v) => {
        if(registerNumber == 0){
          value[0] = (v & 0x00ff) -1;
          value[0]= Math.floor(value[0]*1.01);
          if(value[0] != valueOld[0]){
            $("#data"+0).set("+blink -nomal");
            $("#data"+0).set("innerHTML",value[0]);
          }else{
            $("#data"+0).set("-blink +nomal");
          }
          valueOld[0] = value[0];

          value[1] = ((v & 0xff00) >> 8) - 1;
          value[1]= Math.floor(value[1]*1.01);
          if(value[1] != valueOld[1]){
            $("#data"+1).set("+blink -nomal");
            $("#data"+1).set("innerHTML",value[1]);
          }else{
            $("#data"+1).set("-blink +nomal");
          }
          valueOld[1] = value[1];
        }else{
          value[2] = (v & 0x00ff) -1;
          value[2]= Math.floor(value[2]*1.01);
          if(value[2] != valueOld[2]){
            $("#data"+2).set("+blink -nomal");
            $("#data"+2).set("innerHTML",value[2]);
          }else{
            $("#data"+2).set("-blink +nomal");
          }
          valueOld[2] = value[2];

          value[3] = ((v & 0xff00) >> 8) - 1;
          value[3]= Math.floor(value[3]*1.01);
          if(value[3] != valueOld[3]){
            $("#data"+3).set("+blink -nomal");
            $("#data"+3).set("innerHTML",value[3]);
          }else{
            $("#data"+3).set("-blink +nomal");
          }
          valueOld[3] = value[3];
        }
        registerNumber++;
        if(registerNumber > 1){
          registerNumber = 0;
        }

        console.log("values 1:"+value[0]+" 2:"+value[1]+" 3:"+value[2]+" 4:"+value[3]);
      },(error) => {
        console.log("read error:"+error);
      });

    },50);
  },(v) => {
    console.log("digipot init error:"+v);
  });  
}).catch((e) => {
  console.error("digipot I2C bus error!", e);
});


});

