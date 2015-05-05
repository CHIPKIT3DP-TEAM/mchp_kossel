// Wade's Extruder Gears using Parametric Involute Bevel and Spur Gears by GregFrost
// by Nicholas C. Lewis (A RepRap Breeding Program)
// addition of double helix gears by Stoffel15 - 2010
// addition of resolution controls by Kyle P. Ronan - 2013

// It is licensed under the Creative Commons - GNU GPL license.
// © 2010 by Nicholas C. Lewis
// http://www.thingiverse.com/thing:4305

// For changing the resolution of the change involute_facets and circle_facets.
//	invoulte_facets controls the number of faces on a gear tooth
// circle_facets is a multiplier that increase the number of faces cylinder used to make the gears
// Values of 5 and 1.2 respecitvely are close the original herringbone_gears.scad file
//	If you are making new gears start with 5 and 1.2 so that rendering times are faster. 
// When involute_facets =12 and circle_facets =7 it can take a few minutes to render. 
// 


use <mendel_misc.inc>
use <parametric_involute_gear_v5.1.scad>

//WadeL_double_helix();  //this module call will make the large double helix gear
WadesS_double_helix(); //this module call will make the small double helix gear

module WadeL_double_helix(){
	//Large WADE's Gear - Double Helix
	//rotate([0,0,-2])translate([0,0,0])color([ 100/255, 255/255, 200/255])import_stl("39t17p.stl");

	num_holes=7;
	hole_offset=18;
	hole_size=5;
	circles=0;
	teeth=43; // 47
	pitch=268;
	twist=200;
	height=10;
	nut_height=13;
	bore=8.5;
	pressure_angle=30;
	involute_facets=12;	
	circle_facets=7;

	difference(){
		union(){
		gear (number_of_teeth=teeth,
			circular_pitch=pitch,
			pressure_angle=pressure_angle,
			clearance = 0.2,
			gear_thickness =0,
			rim_thickness = height/2,
			rim_width = 4,
			hub_thickness = nut_height + 4 - height/2,
			hub_diameter = 22,
			bore_diameter = bore,
			circles=circles,
			twist = twist/teeth,
			involute_facets = involute_facets,
			circle_facets = circle_facets);
		mirror([0,0,1])
		gear (number_of_teeth=teeth,
			circular_pitch=pitch,
			pressure_angle=pressure_angle,
			clearance = 0.2,
			gear_thickness = height/2,
			rim_thickness = height/2,
			rim_width = 5,
			hub_thickness = height/2,
			hub_diameter=25,
			bore_diameter=bore,
			circles=circles,
			twist=twist/teeth,
			involute_facets = involute_facets,
			circle_facets = circle_facets);
		}
		//translate([0,0,3])rotate([180,0,0])m8_hole_vert_with_hex(100);

		//Instead of making changes to mendel_misc.inc with higher resoultion,
		//the bolt hole is made the old fashion way with higher resoulution below
			translate ([0,0,nut_height-3]) hexagon(height=14,depth=6);

	color([0,0,1])
		for (hole=[0:num_holes-1])
		{
			rotate([0,0,360/num_holes*hole])
			translate([hole_offset,0,0])
			rotate(30)
			translate([0,0,-height/2-1])
			{
				cylinder(r=hole_size,h=height+2);
				cube([hole_size,hole_size,height+2]);
			}
		}
	}
}

module WadesS_double_helix(){
	//small WADE's Gear
	//rotate([180,0,-23.5])translate([-10,-10,-18])color([ 100/255, 255/255, 200/255])import_stl("wades_gear.stl");

	teeth=13; // 9
	pitch=268;
	twist=200;
	height=10;
	base = 7;
	pressure_angle=30;
	involute_facets=12;	
	circle_facets=7;

	difference(){
		union(){
		gear (number_of_teeth=teeth,
			circular_pitch=pitch,
			pressure_angle=pressure_angle,
			clearance = 0.2,
			gear_thickness =  height/2,
			rim_thickness = height/2,
			rim_width = 5,
			hub_thickness = height/2+base,
			hub_diameter = 20,
			bore_diameter = 5,
			circles=0,
			twist = twist/teeth,
			involute_facets = involute_facets,
			circle_facets = circle_facets);
		mirror([0,0,1])
		gear (number_of_teeth=teeth,
			circular_pitch=pitch,
			pressure_angle=pressure_angle,
			clearance = 0.2,
			gear_thickness =  height/2,
			rim_thickness =  height/2,
			rim_width = 5,
			hub_thickness = height/2,
			hub_diameter=20,
			bore_diameter=5,
			circles=0,
			twist=twist/teeth,
			involute_facets = involute_facets,
			circle_facets = circle_facets);
		}
		translate([0,-5,base+1])cube([6.5,2.7,9],center = true);
		translate([0,0,base+1])rotate([0,90,-90])cylinder(r=1.7,h=20,$fn=circle_facets*4);
	}
}
