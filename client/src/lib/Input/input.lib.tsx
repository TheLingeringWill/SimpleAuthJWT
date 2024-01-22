import React, { forwardRef } from 'react';

import type InputProps from './input.props';

/**
 * A custom input component that forwards the ref to the underlying input element.
 *
 * @param {InputProps} props - Props for the input element.
 * @param {React.Ref<HTMLInputElement>} ref - Ref to the input element.
 * @returns {JSX.Element} - The custom input component.
 */
const Input = forwardRef<HTMLInputElement, InputProps>(
  (props, ref): JSX.Element => {
    return (
      <input
        ref={ref}
        {...props}
      />
    );
  },
);

export default Input;
