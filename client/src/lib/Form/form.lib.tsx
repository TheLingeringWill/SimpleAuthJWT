'use client';

import React from 'react';
import { useForm, type FieldValues } from 'react-hook-form';
import type FormProps from './form.props';

/**
 * A reusable form component for managing form state and submissions.
 *
 * @template TFormValues - The type for form values.
 * @param {FormProps<TFormValues>} props - The props for the Form component.
 * @returns {JSX.Element} - The Form component.
 */
const Form = <TFormValues extends FieldValues>({
  defaultValues,
  onSubmit,
  action,
  formProps,
  children,
}: FormProps<TFormValues>) => {
  const methods = useForm<TFormValues>({
    reValidateMode: 'onBlur',
    ...defaultValues,
  });
  return (
    <form
      onSubmit={methods.handleSubmit(onSubmit)}
      action={action}
      {...formProps}
    >
      {children(methods)}
    </form>
  );
};

export default Form;
