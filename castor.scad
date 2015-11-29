//1 in =25.4 mm
//15/16" = .9375
//23.8125 mm
// all values in mm
//bpw 9/17/14 initial design
//9/18 tweaked marble size
//12/16/14  Increased the height from 20 to 25

//small marble 23.8125
//med marble 24
//big marble 24.25
//bigger 24.5 - works with most, but still tight



 $fn=50;


marbleSize = 23.8125;
marbleOffset = 1; // 0.5mm on each side
baseHeight = 25; //up to the top of where is starts to turn in

cylinderSize = 15.5;  //radius

module castor() {

difference(){
difference(){
difference(){
difference() {
	union(){
		cylinder(r=cylinderSize ,h=baseHeight);
		translate([0,0,baseHeight  ])
			{sphere(r=cylinderSize , center = true);}
	}
	//inside ball
	translate([0,0,baseHeight  ])
		{sphere(r=marbleSize/2 + marbleOffset, center = true);}
}
//cut the top off
translate([-50,-50,baseHeight+4 ]){cube([100,100,50]);}
}
//cut the slot off
translate([-50,-1,baseHeight-4]){cube([100,2,100]);}
}
//cut out the middle cylinder
translate([0,0,0]){cylinder(r=8 ,h=baseHeight+5);}
}

}

castor();