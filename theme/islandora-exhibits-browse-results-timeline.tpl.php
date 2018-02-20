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
    #$img_url = $base_url . "/" . $object['thumbnail_url'];
    $dt = $list_fields['dt'];
    $img_url = $base_url . "/islandora/object/" . $object['PID'] . "/datastream/$dt/view";
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

