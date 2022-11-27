
const coucouModule = require('./coucouModule.node');
console.log('coucou module',coucouModule.coucouFonc('WaRtrO'));

const helloWorldModule = require('./helloModule.node');
console.log('helloWorld module',helloWorldModule.helloWorld());

const additionModule = require('./additionModule.node');
console.log('addition module',additionModule.additionCalc(75,20));

const multiplicationModule = require('./multiplicationModule.node');
console.log('multiplication module',multiplicationModule.multiplicationCalc(2,4));
