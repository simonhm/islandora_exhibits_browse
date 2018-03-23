<?php

/**
 * Admin form building function.
 */
function islandora_exhibits_browse_admin_settings($form, &$form_state) {
  // Include admin CSS file.
  $admin_css = drupal_get_path('module', 'islandora_exhibits_browse') . '/css/islandora_exhibits_browse.admin.css';
  drupal_add_css($admin_css);

  $form['exhibits_pages'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  // Fields.
  global $base_url;   // Will point to http://www.example.com
  $page_prefix = variable_get('islandora_exhibits_browse_page_prefix', 'exhibits');
  $link = $base_url . '/' . $page_prefix . '/yourpath';
  $form['exhibits_pages']['islandora_exhibits_browse_fields_data'] = array(
    '#type' => 'item',
    '#title' => t('Exhibits pages'),
    '#description' => t('Save settings for additional empty fields.' . '<br>Click on Configure to setup exhibit pages. Then click on View Page to see your page.<br>Your pages will be at: <a target=_blank href=' . $link . '>' . $link . '</a><br>Also, there are blocks created to display above exhibits browsers. You can find them at <a target=_blank href=' . $base_url . '/admin/structure/block>.../admin/structure/block</a>. Block name: Exhibit Browse - yourpath ...'),
    '#tree' => TRUE,
    '#theme' => 'islandora_exhibits_browse_admin_table',
  );

  // Get fields from variable.
  $fields_data = variable_get('islandora_exhibits_browse_fields_data', array());

  // Add 3 empty fields.
  for ($i = 1; $i <= 3; $i++) {
    $fields_data[] = array('');
  }

  $fields = array();
  foreach ($fields_data as $key => $value) {
    $field = array(
      'pid' => array(
        '#type' => 'textfield',
        '#default_value' => isset($value['pid']) ? $value['pid'] : '',
      ),
      'type' => array(
        '#type' => 'select',
        '#options' => array(
          '' => t(''),
          'Timeline' => t('Timeline'),
          'Slideshow' => t('Slideshow'),
        ),
        '#default_value' => isset($value['type']) ? $value['type'] : '',
      ),
      'path' => array(
        '#type' => 'textfield',
        '#default_value' => isset($value['path']) ? $value['path'] : '',
      ),
    );
    $fields[] = $field;
  }

  // Add fields.
  $form['exhibits_pages']['islandora_exhibits_browse_fields_data']['fields'] = $fields;

  $form['page_prefix'] = array(
     '#type' => 'textfield',
     '#title' => t('Exhibits Page URL prefix'),
     '#description' => t('Allows control of the path for Islandora Exhibits Browse pages ' .
       '("exhibits" by default).  Changing this value will require you to ') . 
       l('Clear all caches', 'admin/config/development/performance') . t(' before the change will ' .
       'take effect'),
     '#default_value' => $page_prefix,
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 50,
  );

  return $form;
}

/**
 * Theme callback.
 */
function theme_islandora_exhibits_browse_admin_table(&$vars) {

  $fields_data = variable_get('islandora_exhibits_browse_fields_data');

  // Set variable.
  $rows = array();
  $form = $vars['form'];
  $page_prefix = variable_get('islandora_exhibits_browse_page_prefix', 'exhibits');

  // Render islandora_solr_primary_display_table.
  foreach ($form['fields'] as $key => $elements) {

    $found = false;

    $row = array();
    // Check if $key is really the array we need. we shouldn't select the
    // #parent array for example.
    if (is_array($elements) && element_child($key)) {

      $row[] = array('data' => drupal_render($form['fields'][$key]['pid']));      
      $row[] = array('data' => drupal_render($form['fields'][$key]['type']));
      $row[] = array('data' => drupal_render($form['fields'][$key]['path']));

      if ($elements['pid']['#value']) {
        if (@$fields_data[$key]['configuration']) {
          global $base_url;   // Will point to http://www.example.com
          $link = $base_url . '/' . $page_prefix . '/' . @$fields_data[$key]['path'];
          $row[] = "<a href=exhibits_browse/edit?key=" . $key . "&new=0>Configure</a> | <a href=exhibits_browse/remove?key=" . $key . "&new=0>Remove</a> | <a target=_blank href=" . $link . ">View Page</a>";
        } else {
          $row[] = "<a href=exhibits_browse/edit?key=" . $key . "&new=1>Configure</a> | <a href=exhibits_browse/remove?key=" . $key . "&new=1>Remove</a>";
        }
      }
     
      $rows[] = $row;
    }
  }

  // Individual table headers.
  $header = array();
  $header[] = array('data' => t('Collection PID'));
  $header[] = array('data' => t('Type'));
  $header[] = array('data' => t('Path'));
  $header[] = array('data' => t('Operations'));

  // Render table.
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array(
      'id' => 'islandora-exhibits-browsers-admin-table',
    ),
  ));

  return $output;
}

/**
 * Implements hook_validate().
 */
function islandora_exhibits_browse_admin_settings_validate($form, &$form_state) {

  // On save.
  if ($form_state['clicked_button']['#id'] == 'edit-submit') {

    // Check for valid paths.
    foreach ($form_state['values']['islandora_exhibits_browse_fields_data']['fields'] as $key => $value) {
      if (!preg_match("/^[a-zA-Z0-9-_]*$/", $value['path'])) {
        form_set_error('islandora_exhibits_browse_fields_data][fields][' . $key . '][path', t('The path can only contain the following characters: a-z, A-Z, 0-9, - and _'));
      }
    }

  }
}

function islandora_exhibits_browse_admin_settings_submit($form, &$form_state) {
  // Set variables.
  // Clean up array.
  $fields_data = $form_state['values']['islandora_exhibits_browse_fields_data']['fields'];
  $fields_data_configure = variable_get('islandora_exhibits_browse_fields_data');

  foreach ($fields_data as $key => $value) {
    if (empty($value['solr_field']) AND empty($value['label']) AND empty($value['path'])) {
      unset($fields_data[$key]);
    }
  }

  foreach ($fields_data as $key => $value) {    
    $fields_data[$key]['configuration'] = @$fields_data_configure[$key]['configuration'];
  }
  variable_set('islandora_exhibits_browse_fields_data', $fields_data);
  variable_set('islandora_exhibits_browse_page_prefix', $form_state['values']['page_prefix']);

  drupal_set_message(t('The configuration options have been saved.'));
}

function islandora_exhibits_browse_admin_settings_configure($form, &$form_state) {

  $fields_data = variable_get('islandora_exhibits_browse_fields_data');   
  $key = $_GET['key'];
  $new = $_GET['new'];

  $title = 'Exhibit Page';
//  $headline = 'dc.title';
//  $description = 'dc.description';
//  $start_date = 'dc.date_ss';
//  $end_date = '';

  if ($new == 0) {
    $title = $fields_data[$key]['configuration']['title'];
  }
  
  $form['title_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Pagename'),
    '#description' => t('Name of page'),
    '#default_value' => $title,
  );
 
  // Timeline form
  if ($fields_data[$key]['type'] == 'Timeline') {
 
    $headline = isset($fields_data[$key]['configuration']['timeline']['headline']) ? $fields_data[$key]['configuration']['timeline']['headline'] : 'dc.title';
    $description = isset($fields_data[$key]['configuration']['timeline']['description']) ? $fields_data[$key]['configuration']['timeline']['description'] : 'dc.description';
    $start_date = isset($fields_data[$key]['configuration']['timeline']['start_date']) ? $fields_data[$key]['configuration']['timeline']['start_date'] : 'dc.date';
    $end_date = isset($fields_data[$key]['configuration']['timeline']['end_date']) ? $fields_data[$key]['configuration']['timeline']['end_date'] : '';
    $height = isset($fields_data[$key]['configuration']['timeline']['height']) ? $fields_data[$key]['configuration']['timeline']['height'] : '600px';

  
    $form['headline'] = array(
      '#type' => 'textfield',
      '#title' => t('Headline Field'),
      '#description' => t('What field to use for title of object'),
       '#default_value' => $headline,
    );
    $form['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description Field'),
      '#description' => t('What field to use for description of object'),
      '#default_value' => $description,
    );
    $form['start_date'] = array(
      '#type' => 'textfield',
      '#title' => t('Start Date Field'),
      '#description' => t('(required)'),
      '#default_value' => $start_date,
    );
    $form['end_date'] = array(
      '#type' => 'textfield',
      '#title' => t('End Date Field'),
      '#description' => t('(optional)'),
      '#default_value' => $end_date,
    );
    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#description' => t('Height of timeline. For example: 600px, 50% ...'),
      '#default_value' => $height,
    );

  }

  // Slideshow form
  if ($fields_data[$key]['type'] == 'Slideshow') {

    $headline = isset($fields_data[$key]['configuration']['slideshow']['headline']) ? $fields_data[$key]['configuration']['slideshow']['headline'] : 'dc.title';
    $description = isset($fields_data[$key]['configuration']['slideshow']['description']) ? $fields_data[$key]['configuration']['slideshow']['description'] : 'dc.description';
    $height = isset($fields_data[$key]['configuration']['slideshow']['height']) ? $fields_data[$key]['configuration']['slideshow']['height'] : '500px';
    $width = isset($fields_data[$key]['configuration']['slideshow']['width']) ? $fields_data[$key]['configuration']['slideshow']['width'] : '100%';

    $form['headline'] = array(
      '#type' => 'textfield',
      '#title' => t('Headline Field'),
      '#description' => t('What field to use for title of object'),
       '#default_value' => $headline,
    );
    $form['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description Field'),
      '#description' => t('What field to use for description of object'),
      '#default_value' => $description,
    );
    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#description' => t('Height of slideshow. For example: 500px, 50% ...'),
      '#default_value' => $height,
    );
    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#description' => t('Width of slideshow. For example: 500px, 100% ...'),
      '#default_value' => $width,
    );


  }

  // Map browse form
  if ($fields_data[$key]['type'] == 'Map') {
    $form['coming'] = array(
      '#type' => 'textfield',
      '#title' => t('Coming soon'),
      '#default_value' => 'In Progress of development',
    );
  }

  // Submit button.
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 50,
  );

  return $form;  
}

function islandora_exhibits_browse_admin_settings_configure_submit($form, &$form_state) {

  $fields_data = variable_get('islandora_exhibits_browse_fields_data');
  $key = $_GET['key'];
  $new = $_GET['new'];

  $fields_data[$key]['configuration']['title'] = $form_state['values']['title_page'];

  // Timeline.
  if ($fields_data[$key]['type'] == 'Timeline') {
    $fields_data[$key]['configuration']['timeline']['headline'] = $form_state['values']['headline'];
    $fields_data[$key]['configuration']['timeline']['description'] = $form_state['values']['description'];
    $fields_data[$key]['configuration']['timeline']['start_date'] = $form_state['values']['start_date'];
    $fields_data[$key]['configuration']['timeline']['end_date'] = $form_state['values']['end_date'];
    $fields_data[$key]['configuration']['timeline']['height'] = $form_state['values']['height'];
   
    unset($fields_data[$key]['configuration']['slideshow']);
    unset($fields_data[$key]['configuration']['map']);
  }

  // Slideshow.
  if ($fields_data[$key]['type'] == 'Slideshow') {

    $fields_data[$key]['configuration']['slideshow']['headline'] = $form_state['values']['headline'];
    $fields_data[$key]['configuration']['slideshow']['description'] = $form_state['values']['description'];
    $fields_data[$key]['configuration']['slideshow']['height'] = $form_state['values']['height'];
    $fields_data[$key]['configuration']['slideshow']['width'] = $form_state['values']['width'];

    unset($fields_data[$key]['configuration']['timeline']);
    unset($fields_data[$key]['configuration']['map']);
  }
 
  // Map browse.
  if ($fields_data[$key]['type'] == 'Map') {

    unset($fields_data[$key]['configuration']['timeline']);
    unset($fields_data[$key]['configuration']['slideshow']);
  }

  variable_set('islandora_exhibits_browse_fields_data', $fields_data);
  drupal_set_message(t('The configuration options have been saved.'));

  $form_state['redirect'] = 'admin/islandora/tools/exhibits_browse';
}

function islandora_exhibits_browse_admin_settings_remove($form, &$form_state) {
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Remove'),
    '#weight' => 50,
  );

  return $form;
}

function islandora_exhibits_browse_admin_settings_remove_submit($form, &$form_state) {
  $fields_data = variable_get('islandora_exhibits_browse_fields_data');
  $key = $_GET['key'];
  $new = $_GET['new'];
    
  $i = 0;
  if (count($fields_data) > 1) {
    foreach ($fields_data as $k => $value) {
      if ($k != $key) {
        $fields_data_removed[$i] = $fields_data[$k];
        $i = $i + 1;
      }
    }
  } else {
    $fields_data_removed = null;
  }
  variable_set('islandora_exhibits_browse_fields_data', $fields_data_removed);
  drupal_set_message(t('The page has been removed.'));
 
  $form_state['redirect'] = 'admin/islandora/tools/exhibits_browse';
}


