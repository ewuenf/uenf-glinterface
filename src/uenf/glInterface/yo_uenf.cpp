
todo:

  * render-update-queue-threading
  * Fenster / kontext
  * input / time
  * Animation
  * Text
  * Shaderklasse


uenf-gui:


// DrawableCategory references a certain drawable that is the drawable
behind all gui elements of that category // This is just needed for
organization of drawables in gui-library, so that they can eas class
enum DrawableCategory : uint16 {
  Splash,
  Background,
  Button,
  Menu,
  TextLabel,        // has a string-based map identifying subcategories
depending on the font (and thus the associated texture) User = (2 <<
12)  // free category for library extensions by users, implies a
string-based map too }

class DrawableCategoryIndex
{
  DrawableCategory category;
  int16 subIndex;
};

