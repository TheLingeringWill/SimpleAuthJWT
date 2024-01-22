import type { FieldValues, RegisterOptions } from 'react-hook-form';

/**
 * Represents the properties for an input field in a form.
 *
 * @template TFormValues - The type for form values.
 * @typedef {Object} InputFormAuthProps
 * @property {string} type - The input field type.
 * @property {keyof TFormValues} name - The name associated with the form value.
 * @property {RegisterOptions<TFormValues>} registerOpt - Options for registration in the form.
 * @property {string} placeholder - The input field placeholder text.
 * @property {string} srcImage - The image source for the input field.
 * @property {string} errorMessage - The error message for the input field.
 */
type InputFormAuthProps<TFormValues extends FieldValues> = {
  type: string;
  name: keyof TFormValues;
  registerOpt: RegisterOptions<TFormValues>;
  placeholder: string;
  srcImage: string;
  errorMessage: string;
};

export default InputFormAuthProps;
