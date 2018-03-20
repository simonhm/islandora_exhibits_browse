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

For detailed documentation go to: https://islandora.mnpals.net/pals/islandora/object/PALSrepository%3A429

For a video on how to use: https://youtu.be/kXzbCtD7XO4

To configure, go to Home --> Administration --> Islandora --> Islandora Utility Modules --> Exhibits Browse. 

Login as repository manager/administrator.  

First you need a collection PID: Navigate to the collection that will become an exhibit.  Click on Manage.  Click on Datastreams.
Next copy the "Collection PID".  For example: DEMOrepository:exhibit_demo (above "MIME TYPE" column). 

Next navitage to Exhibits Browse configuration (Home --> Administration --> Islandora --> Islandora Utility Modules --> Exhibits Browse).

![Configuration](http://iprotion.com/sites/default/files/2018-03/exhibits.jpg)

In "Exhibits pages", in first column, paste the "Collection PID".  

In second column, choose the Type of exhibit (timeline or slideshow).

In the third column, type in your custom path name.  For example, athletics_slideshow.  Click Save.

Under Operations, click on Configure. 

Under Pagename, name the exhibit.  

The module can display any format - photographs, audio, video, etc. 

Other metadata elements can be used for the headline and description (Dublin Core or MODs).

Click Save.  

Next, click on "View Page" to see what the exhibit would look like.

The pages are located at ..../exhibits/{your-path} 

![Configuration](http://iprotion.com/sites/default/files/2018-03/timeline.JPG)

### Blocks (for Drupal advanced users)

This module also creates blocks displaying those exhibits content as well. After finishing to create the exhibits pages, navigate to .../admin/structure/block, there are some blocks named as: Exhibit Browse - yourpath ... So you have more control to decide where you want these exhibits content to be displayed. For example, you can put a slideshow/timeline block on homepage, etc...

![Blocks](http://iprotion.com/sites/default/files/2018-03/blocks_0.jpg)

### Notes

This module can display video, audio on timeline/slideshow. For other solution pack content, JPG or TN datastream will be used to display.

## Maintainers/Sponsors

Current maintainers:

* [Simon Mai](https://github.com/simonhm)
* Alex Kent (documentation)

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
