**Functionality**

The functionality of the pollution spreading is implemented inside of a SharedVectors file with other functions that also need to be accessed region-wide. Following the rules required industrial zones will be the source of the spreading. The purpose of having pollution in this project is to simulate how pollution would spread in the simulated city that we are given.

**Purpose**

Pollution spreading functionality is implemented within the SharedVectors file, allowing it to be accessed across the entire simulated region. In this setup, industrial zones act as the sole sources of pollution, reflecting real-world industrial pollution sources and simulating the spread of pollution in the virtual city. The SpreadPollution function is called at each time step from main and uses a temporary 2D integer vector to track pollution levels alongside industrial population growth in the UpdatedRegion vector. The function iterates through each cell, spreading pollution to adjacent cells at a decreasing rate of one per step, while bounds checking ensures pollution spreads only within valid cells.

**How data was stored/maintained:**

The Spread Pollution function will be called from the main during each time step and defined inside shared vectors.cpp. Inside this function, there is a temporary 2D integer vector that sets itself equal to the UpdatedRegion integer vector. This is because, as stated in the rules, the industrial population grows at the same rate as pollution for every step. Inside a for loop, the size of UpdateRegion bounds are checked to ensure the pollution spreads to adjacent cells only decreasing by one rate. Outside of the for loop, the temporary vector is set equal to the region pollution vector so it stays updated throughout the program.