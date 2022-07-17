# JExciter
4 band harmonic exciter plugin.


You will need to run cmake on the project in the same fashion as any other aspik project. 
When your project is built you will need to drag in the linkwitz riley filter files into your  Xcode or VS project from source folder. 
If building in mac OS then the GUI will need to be redesigned slightly but plugin should function correctly.

This project was built to showcase the linkwitz riley filter object i built. Currently there is no oversampling in the plugin but I intend to add oversampling 
in the next commit to reduce aliasing in the higher bands.
