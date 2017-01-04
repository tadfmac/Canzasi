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
        value[registerNumber]= v -1;
        value[registerNumber]= Math.floor(value[registerNumber]*1.01);
        if(value[registerNumber] != valueOld[registerNumber]){
          $("#data"+registerNumber).set("+blink -nomal");
          $("#data"+registerNumber).set("innerHTML",value[registerNumber]);
        }else{
          $("#data"+registerNumber).set("-blink +nomal");
        }
        valueOld[registerNumber] = value[registerNumber];
        registerNumber ++;
        if(registerNumber > 3){
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

