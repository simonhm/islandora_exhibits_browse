# Islandora Exhibits Browse 

## Introduction

The Islandora Exhibits Browse module creates exhibits browse pages and blocks from metadata indexed in Solr.

This module will "showcase" Islandora collections as a timeline or slideshow.  We are working on adding a map browse.

## Requirements

This module requires the following modules/libraries:

* [Islandora](https://github.com/islandora/islandora)
* [Tuque](https://github.com/islandora/tuque)
* [Islandora Solr Search](https://github.com/Islandora/islandora_solr_search)

## Installation

Install as usual, see [this](https://drupal.org/documentation/install/modules-themes/modules-7) for further information.

## Configuration

For a short video on setting up an exhibit, see: https://islandora.mnpals.net/pals/islandora/object/PALSrepository%3A426. 
For detailed documentation, see: https://islandora.mnpals.net/pals/islandora/object/PALSrepository%3A427


To configure, go to Home --> Administration --> Islandora --> Islandora Utility Modules --> Exhibits Browse. 

Login as repository manager/administrator.  First navigate to the collection that will become an exhibit.  Click on Manage.  Click on Datastreams.
Next copy the "Collection PID".  For example: DEMOrepository:exhibit_demo (above "MIME TYPE" column).  

Next navitage to Exhibits Browse (Home --> Administration --> Islandora --> Islandora Utility Modules --> Exhibits Browse).

In "Exhibits pages", in first column, copy the "Collection PID".  

In second column, choose the Type of exhibit (timeline or slideshow).

In the third column, type in a custom path name.  For example, athletics_slideshow.  Click Save.

Under Operations, click on Configure. 

Under Pagename, name the exhibit.  

Other metadata elements can be used for the headline and description (Dublin Core or MODs).

Choose the datastream to be used for displaying images in the slideshow or timeline.  For now the objects in the collection 
must be the same format (all JPG or all TIFF, for example).  

Click Save.  

Next, click on "View Page" to see what the exhibit would look like.

## Notes

* ...

### Theming

There are template files for the exhibit pages. 

Template files can be overridden by a theme by copying the template file from the modules folder into the theme folder. You can override a theme per defined facet page by appending the path value to the template file. If you do, make sure to copy the original template file to your theme as well.

## Maintainers/Sponsors

Current maintainers:

* [Simon Mai](https://github.com/simonhm)
* Alex Kent (documentation)

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
