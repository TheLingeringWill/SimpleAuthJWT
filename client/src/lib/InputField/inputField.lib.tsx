import React, { forwardRef } from 'react';

import Input from '@/lib/Input';
import InputFieldProps from './inputField.props';

/**
 * A custom input field component that can contain an input element and an optional image.
 *
 * @param {InputFieldProps} props - The props for the InputField component.
 * @param {React.Ref<HTMLInputElement>} ref - Ref to the input element.
 * @returns {JSX.Element} - The custom input field component.
 */
const InputField = forwardRef<HTMLInputElement, InputFieldProps>(
  ({ inputProps, imageProps, ...other }: InputFieldProps, ref): JSX.Element => {
    return (
      <>
        {Object.keys(other).length ? (
          <div {...other}>
            {imageProps && <img {...imageProps} />}
            <Input
              ref={ref}
              {...inputProps}
            />
          </div>
        ) : (
          <Input
            ref={ref}
            {...inputProps}
          />
        )}
      </>
    );
  },
);

export default InputField;
