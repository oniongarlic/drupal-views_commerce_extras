<?php

class commerce_reference_product_sku_validate extends views_plugin_argument_validate {

  public function option_definition() {
    $options = parent::option_definition();
    $options['sku_preg_match'] = array('default' => '');
    $options['use_product_title'] = array('default' => true);

    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['sku_preg_match'] = array(
      '#type' => 'textfield',
      '#title' => t('SKU preg_match'),
      '#default_value' => $this->options['sku_preg_match']
    );
    $form['use_product_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use product title'),
      '#default_value' => $this->options['use_product_title']
    );
  }

  public function validate_argument($sku) {

    if (!is_string($sku))
        return false;

    $sku=trim($sku);

    if (empty($sku))
        return false;

    if (strpos($sku, ',') !== false)
        return false;

    // We require a bit more checks than that
    if (strlen($sku)<3)
        return false;

    // Optional regular expression match
    if (!empty($this->options['sku_preg_match'])) {
      if (preg_match($this->options['sku_preg_match'], $sku)===false)
        return false;
    }

    // OK, it looks like a valid SKU, check that it exists and loads and if so use it for product title
    $product=commerce_product_load_by_sku($sku);
    if (empty($product))
       return false;

    if ($this->options['use_product_title'])
      $this->argument->validated_title=$product->title;

    return true;
  }
}

