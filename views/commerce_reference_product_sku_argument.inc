<?php

class commerce_reference_product_sku_argument extends views_plugin_argument_default {

  public function option_definition() {
    $options = parent::option_definition();
    $options['sku_preg_match'] = array('default' => '/^[A-Z]{3}(\d{6,9})$/');
    $options['index'] = array('default' => '1');

    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['sku_preg_match'] = array(
      '#type' => 'textfield',
      '#title' => t('SKU preg_match'),
      '#default_value' => $this->options['sku_preg_match'],
    );
    $form['index'] = array(
      '#type' => 'select',
      '#title' => t('Path component'),
      '#default_value' => $this->options['index'],
      '#options' => range(1, 10),
      '#description' => t('The numbering starts from 1, e.g. on the page product/sku123456789, the 2nd path component is "sku123456789".'),
    );
  }

  public function get_argument() {
    $apos=$this->options['index'];
    $sku=arg($apos);

    // Optional regular expression match
    if (!empty($this->options['sku_preg_match'])) {
      if (preg_match($this->options['sku_preg_match'], $sku)===false)
        return false;
    }

    $product=commerce_product_load_by_sku($sku);

    return empty($product) ? NULL : $product->product_id;
 }
}
