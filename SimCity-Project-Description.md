**SimCity Project Description**

**Design Team Members:** Ore Akinbola, Kayden Plemons, Jared Beyers, Luke Rivera, Aidan Birmingham.

**Overview:** The purpose of this project is to create a simulated city with different residential, commercial, and industrial zones. The simulation will grow with factors of population and pollution as the region grows. The goal is to be able to tell how pollution impacts the overall development. The factors of growth depend on goods, workers, and energy within the region. Using data structures with abstract data types to program the simulation to run efficiently.  

**Major functionality components:** 

[1. Reading Config/Region File & Initializing](Reading Config & Initializing): The config and region files provide critical data for the city's layout and simulation parameters. After reading these files, the simulation is initialized and the city's growth and activity are tracked. This component creates the shared region vectors to help the functionality access the region tiles.

[2. Residential Functionality](Residential Functionality): Residential zones grow or decline based on proximity to power lines, population density, and their ability to supply workers to industrial and commercial zones. The simulation models this movement at each step. This component will use shared region vectors to help analyze the Residential tiles and then decide when to grow. 

[3. Industrial Functionality](Industrial Functionality): Industrial functionality depends on factors like power availability and workforce from residential zones. The simulation tracks the growth of industrial tiles based on these interactions. This component will use shared region vectors to help analyze the Industrial tiles and then decide when to grow. 

[4. Commercial Functionality](Commercial Functionality): The commercial zone checks for power, population, and goods, coordinating with industrial and residential zones. Growth is simulated at each time step following specific rules. This component will use shared region vectors to help analyze the commercial tiles and then decide when to grow. 

[5. Pollution Functionality](Pollution Functionality): Pollution simulates its spread throughout the city, primarily driven by the industrial zone. The simulation updates at each time step, modeling the impact of industrial activity on pollution levels. This component will use shared region vectors to help analyze the zones and then decide when to pollute cells. 

[6. Analysis Of The Region & Area](Analysis Of The Region & Area): Once the main program is executed, the industrial, residential, and other components collaborate, culminating in a final analysis of the region. The program will output the region state and workers/goods depending on the given time steps.

![SimCity_Design__1_](uploads/c3ac10862a1d5e2ff1523b9a2b90477d/SimCity_Design__1_.png)