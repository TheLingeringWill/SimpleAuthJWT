import React from 'react';

import type {
  FieldValues,
  UseFormProps,
  UseFormReturn,
  SubmitHandler,
} from 'react-hook-form';

/**
 * Props for a generic form component.
 *
 * @interface FormProps
 * @template TFormValues - The type for form values.
 */
type FormProps<TFormValues extends FieldValues> = {
  /**
   * The default values for the form
   *
   * @type {TFormValues}
   */
  defaultValues?: UseFormProps<TFormValues>;

  /**
   * The submit handler function for the form.
   *
   * @type {SubmitHandler<TFormValues>}
   */
  onSubmit: SubmitHandler<TFormValues>;

  /**
   * A function that receives the form methods and returns the form's children components.
   *
   * @type {(methods: UseFormReturn<TFormValues>) => React.ReactNode}
   */
  children: (methods: UseFormReturn<TFormValues>) => React.ReactNode;

  action?: string | ((formData: FormData) => void);

  /**
   * Additional props for the form element.
   *
   * @type {React.FormHTMLAttributes<HTMLFormElement>}
   */
  formProps?: React.FormHTMLAttributes<HTMLFormElement>;
};

export default FormProps;
