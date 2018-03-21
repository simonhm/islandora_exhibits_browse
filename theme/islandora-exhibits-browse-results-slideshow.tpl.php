
  <div class="slideshow-shm">

<?php

  $i = 0;
  $page_data = $results;
  foreach ($page_data as $key => $object) {
    $pid = $object['PID'];
    global $base_url;

    $object_url = "$base_url/" . $object['object_url'];

    $cm = $object['content_models'][0];
    if ($cm == "info:fedora/islandora:sp_large_image_cmodel") {
       $img_url = $base_url . "/islandora/object/" . $object['PID'] . "/datastream/JPG/view";
       $cover = "<a href=$object_url><img src=$img_url></a>";
    } elseif ($cm == "info:fedora/islandora:sp_basic_image") {
       $img_url = $base_url . "/islandora/object/" . $object['PID'] . "/datastream/MEDIUM_SIZE/view";
       $cover = "<a href=$object_url><img src=$img_url></a>";
    } elseif ($cm == "info:fedora/islandora:sp_videoCModel") {
       $cover = '<video id="my-video" class="video-js" controls preload="auto" width=500px height=400px poster="' . $base_url . "/islandora/object/" . $object['PID'] . "/datastream/TN/view" . '" data-setup="{}"><source src="'  
              . $base_url . "/islandora/object/" . $object['PID'] . "/datastream/MP4/view" . '" type="video/mp4"><p class="vjs-no-js">To view this video please enable JavaScript, and consider upgrading to a web browser that<a href="http://videojs.com/html5-video-support/" target="_blank">supports HTML5 video</a></p></video>';
    } elseif ($cm == "info:fedora/islandora:sp-audioCModel") {
       $cover = '<video id="my-video" class="video-js" controls preload="auto" width=500px height=300px poster="' . $base_url . "/islandora/object/" . $object['PID'] . "/datastream/TN/view" . '" data-setup="{}"><source src="' 
              . $base_url . "/islandora/object/" . $object['PID'] . "/datastream/PROXY_MP3/view" . '" type="audio/mp3"><p class="vjs-no-js">To view this video please enable JavaScript, and consider upgrading to a web browser that<a href="http://videojs.com/html5-video-support/" target="_blank">supports HTML5 video</a></p></video>';      
    } else {
       $img_url = $base_url . "/islandora/object/" . $object['PID'] . "/datastream/TN/view";
       $cover = "<a href=$object_url><img src=$img_url></a>";
    }
    
    if (is_array(@$object['solr_doc'][$list_fields['headline']])) {
      $headline = @$object['solr_doc'][$list_fields['headline']][0];
    } else {
      $headline = @$object['solr_doc'][$list_fields['headline']];
    }
    $headline = str_replace("'","",$headline);
    $headline= htmlentities($headline);
    $headline = "<a href=$base_url/" . $object['object_url'] . ">$headline</a>";
    if (is_array(@$object['solr_doc'][$list_fields['description']])) {
      $description = @$object['solr_doc'][$list_fields['description']][0];
    } else {
      $description = @$object['solr_doc'][$list_fields['description']];
    }
    $description = str_replace("'","",$description);
    $description = str_replace("\n","",$description);
    $description = str_replace("\r","",$description);
    $description = htmlentities($description);
   
    $object_url = "$base_url/" . $object['object_url'];

    echo "<div class=content>$cover<div class=caption><div class=title><a href=#>$headline</a></div><div class=description>$description</div></div></div>";

    $h = $list_fields['height'];
    $w = $list_fields['width'];

  }
?>

  </div>

  <script type="text/javascript">

    jQuery(function ($) {

      $('.slideshow-shm').slick({
        autoplay: true,
        autoplaySpeed: 2000,

        dots: false,
        infinite: true,
        speed: 500,
        fade: true,
        cssEase: 'linear'

      });

    });

  </script>


<style>

.slick-slider {
  text-align: center;
<?php
  echo "width:$w;";
?>
}

.slick-slide {
<?php
  echo "height:$h;";
?>
  width: 100%;
}

.slick-slide .content {
  width: 100%;
}

.slick-slide img {
  height: 100%;
  margin:auto;
}

.slick-prev {
  display: block;
    position: absolute;
    top: 0;
    left: 0;
    z-index: 100;
    opacity: 0.5;
    margin-top: 8px!important;
    margin-left: 5px!important;
}

.slick-next {
  float: right;
  position: absolute;
    top: 0;
    right: 0;
    z-index: 100;
    opacity: 0.5;
    margin-top: 8px!important;
    margin-right: 5px!important;
}

.slick-prev:hover, .slick-next:hover  {
  opacity: 1;
}

.slick-slider ul li {
  list-style: none;
  float: left;
}

.slick-slider .slick-dots {
  display: inline-block;
}

.slick-slide .caption {
    text-align: center;
    background-color: rgba(0, 0, 0, 0.5);
    position: absolute;
    z-index: 100;
    bottom: 0;
    width: 100%;
    padding: 8px;
}

.slick-slide .title a {
  color: #fff!important;
  font-weight: bold;
}

.slick-slide .description {
  color: #fff!important;
}

</style>  
