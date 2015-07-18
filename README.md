# emotion-game
A small project I created to practice OpenGL and game programming.

If you would like to play, download /download/playable.zip.

A small, little game loosly inspired by Inside Out. You control a white block using WQWE/ASD/ZXC keys (S corresponding to stop, W/D/X/A corresponding to the cardinal directions, and Q/E/C/Z corresponding to those inbetwen). You have a queue of 100 objects, and any time your block comes into contact with any other (which are of type Joy(yellow), Sadness(blue), Anger(red), Disgust(green), and Fear(pink)) in the active area, you collect that object while disregarding the one at the front of your queue. The goal is to have an equal amout of objects in your queue. The bottom shelf tells you which sprites you need more of (indicated by a plus sign) or less of (indicated by a minus sign). The "active" sprite (i.e. the one to be disregarded next) is indicated by its brightness/not being faded.

# Basic Changes Needed
- Add all dependency files to a folder within the project.
- Vital game information held within in the shelf is in too awkward of a position. It requires the player to distract themselves from the game and look away from the ActiveArea while the game is running. The proposed solution is to add a colored internal square to the user's block indicating what type of Sprite they should connect next.
- The green on the shelf is difficult to notice when it is next to be removed from the queue.
- Consider using W/A/S/D as simplified command keys rather than the current nine.

# Advanced Changes Desire
- Give the blocks personality
- Add "animation" to dying and spawning sprites
