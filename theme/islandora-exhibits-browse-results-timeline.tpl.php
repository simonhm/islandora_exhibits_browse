<?php

  function sYear($date) {
    return substr($date,0,4);
  }

  function sMonth($date) {
    return substr($date,5,2);
  }

  function sDate($date) {
    return substr($date,8,2);
  }

?>

      <div id='timeline-embed' style="width: 100%; height: 600px"></div>
<style>
#timeline-embed {
<?php
  $h = $list_fields['height'];
  echo "height:$h!important;";
?>
}
</style>
      <script type="text/javascript">

          var timeline_json_text = '{' +
'    "events": [' +
<?php

  $i = 0; 
  $page_data = $results;
  foreach ($page_data as $key => $object) {
    $pid = $object['PID'];
    global $base_url;
 
    $cm = $object['content_models'][0];
    if ($cm == "info:fedora/islandora:sp_large_image_cmodel") {
       $img_url = $base_url . "/islandora/object/" . $object['PID'] . "/datastream/JPG/view.jpg";
       $cover = "<a href=$object_url><img src=$img_url></a>";
    } elseif ($cm == "info:fedora/islandora:sp_basic_image") {
       $img_url = $base_url . "/islandora/object/" . $object['PID'] . "/datastream/MEDIUM_SIZE/view.jpg";
    } elseif ($cm == "info:fedora/islandora:sp_videoCModel") {
       $img_url = $base_url . "/islandora/object/" . $object['PID'] . "/datastream/MP4/view.mp4";
    } elseif ($cm == "info:fedora/islandora:sp-audioCModel") {
       $img_url = $base_url . "/islandora/object/" . $object['PID'] . "/datastream/PROXY_MP3/view.mp3";
    } else {
       $img_url = $base_url . "/islandora/object/" . $object['PID'] . "/datastream/TN/view.jpg";
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
    if (is_array(@$object['solr_doc'][$list_fields['start_date']])) {
      $start_date = @$object['solr_doc'][$list_fields['start_date']][0];
    } else {
      $start_date = @$object['solr_doc'][$list_fields['start_date']];
    }
    $sYear = sYear($start_date);
    $sMonth = sMonth($start_date);
    $sDate = sDate($start_date);
//    if ($sYear == '') {
//      $sYear = 2017;
//    }
    echo "'      {' +
         '       \"media\": {' +
'          \"url\": \"$img_url\"' +
'        },' +
'        \"start_date\": {' +
'          \"month\": \"$sMonth\",' +
'          \"day\": \"$sDate\",' +
'          \"year\": \"$sYear\"' +
'        },' +
'        \"text\": {' +
'          \"headline\": \"$headline\",' +
'          \"text\": \"$description\"' +
'        }' +
";
    $i = $i + 1;
    if ($i == count($page_data)) {
      echo "'     }' +";
    } else {
      echo "'     },' +";
    }
  }
?>
']' +
'}';
//simon
          var timeline_json = JSON.parse(timeline_json_text);

          window.timeline = new TL.Timeline('timeline-embed', timeline_json);
      </script>

<style>
.tl-media {
  z-index: 999!important;
  display: table-cell;
}

.tl-media video {
  max-height: 100%!important;
}

.tl-slide-scrollable-container {
    margin-left: auto;
    margin-right: auto;
}

.tl-media audio {
  max-height: 100%!important;
}

.tl-text {
  float: left;
  width: 100%!important;
}

</style>
