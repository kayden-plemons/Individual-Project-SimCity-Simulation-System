**Functionality**

The functionality of the Analysis Of The Region & Area is implemented in the SharedVectors file with other functions that also need to be accessed region-wide. Multiple main printing functions represent the population and pollution. The user will be able to input a desired part of the region to analyze, this is done inside one function that shares already collected data from the time stepping. 

**Purpose**

The purpose of the region and area analysis functionality is to enable detailed examination of specific areas within the simulation, allowing users to assess population and pollution metrics across residential, industrial, and commercial zones. This targeted analysis helps users understand localized impacts of growth patterns, pollution spread, and zone density within chosen sections of the city. By accepting user-defined coordinates, the function outputs a breakdown of zone-specific population and pollution within the specified area, offering insights into urban dynamics and resource allocation. This feature enhances the simulation's value by allowing more granular, user-driven insights into the city model.

**How data was stored/maintained:**

The function AnalyzeUserArea is called from the main after the program time steps are completed or exited after no change in steps. AnalyzeUserArea is defined inside of Shared Vectors Files. The user gets outputted to enter valid coordinates to analyze a specific area in the region. The function contains int variables x1, y1, x2, and y2 which represent these coordinates and also is used to compare if the input is in bounds comparing the region height and width. Then using a for loop within giving user bounds it analyzes the StoredRegion vector characters R, I, and C adding the population from UpdatedRegion to integers for each zone population and pollution.