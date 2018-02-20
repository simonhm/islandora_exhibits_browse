<?php

/**
 * Implements hook_preprocess().
 */
function islandora_exhibits_browse_preprocess_islandora_exhibits_browse_results(&$variables) {
  // Add template suggestion based on path name.
  $variables['template_files'][] = 'islandora-exhibits-browse-results--' . $variables['path'];
}

/**
 * Implements hook_preprocess().
 */
function islandora_exhibits_browse_preprocess_islandora_exhibits_browse_wrapper(&$variables) {

  $total = $variables['pager_data']['total'];
  $from = $variables['pager_data']['offset'] + 1;
  $to = $variables['pager_data']['offset'] + $variables['pager_data']['limit'];
  if ($to > $total) {
    $to = $total;
  }

  if ($total > 0) {
    $results_count = t('Showing @from - @to of @total', array(
      '@from' => $from,
      '@to' => $to,
      '@total' => $total,
    ));
  }
  else {
    $results_count = t('No results found.');
  }

  $variables['results_count'] = $results_count;

  // Add template suggestion based on path name.
  $variables['template_files'][] = 'islandora-exhibits-browse-wrapper--' . $variables['path'];
}

