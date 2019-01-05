// Control OSC Orbit //

p = ProxySpace.push(s.boot);
p.makeTempoClock(100/120);
p.quant = 4;
m = NetAddr("127.0.0.1", 5612); // para OpenFrameworks
PirS.start
~onsets = {Onsets.kr(FFT(LocalBuf(512), SoundIn.ar(0)),0.1)};

// Glitch

(

PirV.glitch(0, 0);

// 1 glitch convergence
OSCdef(\glitch1, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 1); // RGB
}, '/glitch1Def');
~glitch1 = {Demand.kr(Impulse.kr(~tempo*1), 0, Drand([1, 0, 0, 0],inf))};
~glitchSend1 = {SendReply.kr(Impulse.kr(~tempo.kr*1), '/glitch1Def', ~glitch1.kr)};
//
OSCdef(\glitch1).free;

// 2 gtlich glow
OSCdef(\glitch2, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 2); // RGB
}, '/glitch2Def');
~glitch2 = {Demand.kr(Impulse.kr(~tempo), 0, Drand([0, 1, 0, 0],inf))};
~glitchSend2 = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/glitch2Def', ~glitch2.kr)};
//
OSCdef(\glitch2).free;

// 3 glitch shaker
OSCdef(\glitch3, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 3); // RGB
}, '/glitch3Def');
~glitch3 = {Demand.kr(Impulse.kr(~tempo), 0, Drand([1, 0, 0, 0],inf))};
~glitchSend3 = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/glitch3Def', ~glitch3.kr)};
//
OSCdef(\glitch3).free;

// 4 glitch cutslider
OSCdef(\glitch4, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 4); // RGB
}, '/glitch4Def');
~glitch4 = {Demand.kr(Impulse.kr(~tempo*12), 0, Drand([1, 0, 0, 0],inf))};
~glitchSend4 = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/glitch4Def', ~glitch4.kr)};
//
OSCdef(\glitch4).free;

// 5 glitch twist
OSCdef(\glitch5, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 5); // RGB
}, '/glitch5Def');
~glitch5 = {Demand.kr(Impulse.kr(~tempo), 0, Drand([1, 0, 0, 0],inf))};
~glitchSend5 = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/glitch5Def', ~glitch5.kr)};
//
OSCdef(\glitch5).free;

// 6 glitch outline
OSCdef(\glitch6, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 6); // RGB
}, '/glitch6Def');
~glitch6 = {Demand.kr(Impulse.kr(~tempo), 0, Drand([0, 0, 0, 0],inf))};
~glitchSend6 = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/glitch6Def', ~glitch6.kr)};
//
OSCdef(\glitch6).free;

// 7 glitch oise
OSCdef(\glitch7, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 7); // RGB
}, '/glitch7Def');
~glitch7 = {Demand.kr(Impulse.kr(~tempo), 0, Drand([0, 0, 0, 0],inf))};
~glitchSend7 = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/glitch7Def', ~glitch7.kr)};
// OSCdef(\glitch7).free;

// 8 glitch slitscan
OSCdef(\glitch8, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 8); // RGB
}, '/glitch8Def');
~glitch8 = {Demand.kr(Impulse.kr(~tempo), 0, Drand([1, 0, 0, 0],inf))};
~glitchSend8 = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/glitch8Def', ~glitch8.kr)};
//
OSCdef(\glitch8).free;

// 9 glitch swell
OSCdef(\glitch9, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 9); // RGB
}, '/glitch9Def');
~glitch9 = {Demand.kr(Impulse.kr(~tempo), 0, Drand([0, 0, 0, 0],inf))};
~glitchSend9 = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/glitch9Def', ~glitch9.kr)};
// OSCdef(\glitch9).free;

// invert
OSCdef(\glitch10, {|msg|
	var data = msg[3];
	m.sendMsg("/glitch", data, 10); // RGB
}, '/glitch10Def');
~glitch10 = {Demand.kr(Impulse.kr(~tempo*10), 0, Drand([0, 1, 0, 1],inf))};
~glitchSend10 = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/glitch10Def', ~glitch10.kr)};
//
OSCdef(\glitch10).free;

)

// Control

(


// feedback X
OSCdef(\feedbackX, {|msg|
	var data = msg[3];
	var data2 = msg[4];
	//msg.postln;
	m.sendMsg("/fbx", data)
}, '/feedbackXDef');
~feedbackXSeq = {Lag.kr(Demand.kr(Impulse.kr(~tempo*2), 0, Drand([ 40, 40, -560, 640]*2,inf)), 8)};
~feedbackXSend = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/feedbackXDef', ~feedbackXSeq.kr)};
// OSCdef(\feedbackX).free;

// feedback Y
OSCdef(\feedbackY, {|msg|
	var data = msg[3];
	var data2 = msg[4];
	//msg.postln;
	m.sendMsg("/fby", data)
}, '/feedbackYDef');
~feedbackYSeq = {Lag.kr(Demand.kr(Impulse.kr(~tempo*2), 0, Drand([ 40, -560, 40, 640]*1, inf)), 8)};
~feedbackYSend = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/feedbackYDef', ~feedbackYSeq.kr)};
//OSCdef(\feedbackY).free;

OSCdef(\orbit, {|msg|
	var data = msg[3];
	m.sendMsg("/orbit", data, 0)
}, '/orbitDef');
~orbitSeq = {Demand.kr(Impulse.kr(~tempo*1), 0, Drand([750.rand2, 450.rand2, 10.rand2, 100.rand2, 20.rand2]*2, inf))};
~orbitSend = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/orbitDef', ~orbitSeq.kr)};
//
OSCdef(\orbit).free;

OSCdef(\camdistance, {|msg|
	var data = msg[3];
	m.sendMsg("/camdistance", data)
}, '/camdistanceDef');
~camdistanceSeq = {Lag.kr(Demand.kr(Impulse.kr(~tempo*1), 0, Drand([600, 100], inf)), 1)};
~camdistanceSend = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/camdistanceDef', ~camdistanceSeq.kr)};
OSCdef(\camdistance).free;

OSCdef(\starsnum, {|msg|
	var data = msg[3];
	Orb.starsnum( data)
}, '/starsnumDef');
~starsnumSeq = {Lag.kr(Demand.kr(Impulse.kr(~tempo*0.5), 0, Drand([600, 100, 10, 200, 1000], inf)), 1)};
~starsnumSend = {SendReply.kr(Impulse.kr(~tempo.kr*30), '/starsnumDef', ~starsnumSeq.kr)};
OSCdef(\camdistance).free;

)


