# emotion-game
A practice project to work with OpenGL and game programming.

A small, little game loosly inspired by Inside Out. You control a white block using WQWE/ASD/ZXC keys (S corresponding to stop, W/D/X/A corresponding to the cardinal directions, and Q/E/C/Z corresponding to those inbetwen). You have a queue of 100 objects, and any time your block comes into contact with any other (which are of type Joy(yellow), Sadness(blue), Anger(red), Disgust(green), and Fear(pink)) in the active area, you collect that object while disregarding the one at the front of your queue. The goal is to have an equal amout of objects in your queue. The bottom shelf tells you which sprites you need more of (indicated by a plus sign) or less of (indicated by a minus sign). The "active" sprite (i.e. the one to be disregarded next) is indicated by its brightness/not being faded.

# Known Issues
- There is no guaranteed path to victory. Say there is a condition where disregarding a yellow and collecting a green will win you the game; there is no guarantee a green sprite will be present. To be fixed next update.

- Once a game is finished, the application must be reopened to start a new one.

- 9 command keys seems clunky.


# Todo
- User control could be more fluid.
- Give the blocks personality
- Add "animation" to dying and spawning sprites
- Pontentially change Fear's color to distinguish it from sadness and/or anger (colorblindness OP)
- Make it more apparent which sprite is "active"
