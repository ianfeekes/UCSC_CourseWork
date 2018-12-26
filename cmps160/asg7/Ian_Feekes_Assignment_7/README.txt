This is the folder for Ian Feekes' assignment7 for cmps160 fall 2018. 
The idea was to implement a game or creative piece involving colour picking and at least one advanced graphics technique. 

I created the virtual rave maze, which is a giant cube maze where the user has a glowstick to light up the scene until he
finds his venue.

-The world has many different geometries. 
-The glowstick is the primary diffuse light source, however once the user reaches the 'venue' area (and wins), the light
source is generated as a random source above the venue in the sky
-You can interact with the glowstick light cube, and any 5 of the uniformly-coloured maze cubes using colour picking with 
 mouse coordinates and center screen coordinates 
-When the glowstick is selected it will change to a random uniform colour (along with the light colour sent to diffuse
 in gl), when the maze cubes are selected they will change to a cyan and the amount of cubes the user can select is 
 decremented 
 
Color picking is involved with: 
	-initially clicking on the glowstick(using mouse coordinates and vector computation) to choose whichever random
         color you like to light your way as you navigate the maze
	-pressing the 'I' key when very close to a maze cube that you are facing in order to mark that cube as 'discovered'
         so that you can track where you've been. 
Advanced graphics techniques: 
	-all the maze cubes use colour blending (which was very easy to implement) 
	-collision with the wall cubes of the maze prevents incrementing the camera if it would mean running into a wall

H will toggle the help message, sent to html, which may be useful if you are confused. 

After hours and hours of debugging this, I understand that it may take a while to reach the venue (and possibly become
tedious after navigating a labyrinth of hundreds of uniformly-coloured cubes) with throbbing ambient light, and because
I don't want to torture the TA's, I think it's best if I give out directions to cheat your way to winning (also so that
its easier for you guys to give me points on 'making a meaningful and engaging experience' of finding the venue)
	-take the first right, and follow as it takes a left snakes in a long corridor
	-when the long hallway forks to the left, go straight rather than taking a left
	-take the next available left and follow it as it snakes along until you find the rave cubes the fluctuate 
	 in colour, and keep going until you enter the large room and you've made it! 

Alternatively, you can spawn in the main venue by going into my main.js file and commenting in lines 56 and 57 which will
initialize the initial camera position to be within the venue if you can't figure your way through the maze.  
