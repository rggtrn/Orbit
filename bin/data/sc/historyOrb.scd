(
q = ();
NetAddr.broadcastFlag = true;
q.addrs = (0..7).collect { |x|
		NetAddr("255.255.255.255", 57120 + x)
};
q.sendAll = { |q ... args|
		q.addrs.do { |addr|
				addr.sendMsg(*args)
		}; ""
}

);


PirV.text(1, 0)

(

PirS.start;
PirS.n.sendMsg("/textON", 1);

History.start;
//History.makeWin;

OSCdef(\hist, { |msg|
	//msg.postln;
	History.enter(msg[2].asString, msg[1]);
}, \hist).fix;

OSCdef(\ofx, { |msg|
	PirS.n.sendMsg("/message", msg[2].asString, msg[1].asString);
z = z.add(msg[2].asString);
if(z.size == 10,
	{z.removeAt(0)
	});
//z.postln;
	//PirS.n.sendMsg("/multimsg", 1, (2300).rand2-600, (1000).rand2+500, 10.rand, 360.rand2, 60.rand2, z[6]);
	//PirS.n.sendMsg("/multimsg", 2, (1300).rand2-600, (1000).rand2+500, 10.rand, 360.rand2, 60.rand2, z[5]);
	//PirS.n.sendMsg("/multimsg", 3, (600).rand2-300, (1000).rand2+500, 10.rand, 360.rand2, 60.rand2, z[4]);
	//PirS.n.sendMsg("/multimsg", 4, (600).rand2-300, (1000).rand2+500, 10.rand, 360.rand2, 60.rand2, z[3]);
	//PirS.n.sendMsg("/multimsg", 5, (600).rand2-300, (1000).rand2+500, 10.rand, 360.rand2, 60.rand2, z[2]);
	//PirS.n.sendMsg("/multimsg", 6, (600).rand2-300, (1000).rand2+500, 10.rand, 360.rand2, 60.rand2, z[1]);

}, \hist);


History.localOff;

History.forwardFunc = { |code|
	//q.sendAll(\hist, \killall, code);
	q.sendAll(\hist, \emi, code);
};

)