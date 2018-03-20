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

For a video on how to use: https://www.youtube.com/edit?video_referrer=watch&video_id=kXzbCtD7XO4 

To configure, go to Home --> Administration --> Islandora --> Islandora Utility Modules --> Exhibits Browse. 

Login as repository manager/administrator.  

First you need a collection PID: Navigate to the collection that will become an exhibit.  Click on Manage.  Click on Datastreams.
Next copy the "Collection PID".  For example: DEMOrepository:exhibit_demo (above "MIME TYPE" column). 

Next navitage to Exhibits Browse configuration (Home --> Administration --> Islandora --> Islandora Utility Modules --> Exhibits Browse).

In "Exhibits pages", in first column, paste the "Collection PID".  

In second column, choose the Type of exhibit (timeline or slideshow).

In the third column, type in a custom path name.  For example, athletics_slideshow.  Click Save.

Under Operations, click on Configure. 

Under Pagename, name the exhibit.  

The module can display any format - photographs, audio, video, etc. 

Other metadata elements can be used for the headline and description (Dublin Core or MODs).

Click Save.  

Next, click on "View Page" to see what the exhibit would look like.

### Blocks (for advanced Drupal users)

This module also creates blocks displaying those exhibits content as well. After finishing to create the exhibits pages, navigate to .../admin/structure/block, there are some blocks named as: Exhibit Browse - yourpath ... So you have more control to decide where you want these exhibits content to be displayed. For example, you can put a slideshow/timeline block on homepage, etc...

### Notes

The module can display video, audio on timeline and slideshow. For other solution pack content, it will use JPG or TN datastream to display them on timeline/slideshow.

### Theming

There are template files for the exhibit pages. 

Template files can be overridden by a theme by copying the template file from the modules folder into the theme folder. You can override a theme per defined facet page by appending the path value to the template file. If you do, make sure to copy the original template file to your theme as well.

## Maintainers/Sponsors

Current maintainers:

* [Simon Mai](https://github.com/simonhm)
* Alex Kent (documentation)

## License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)
