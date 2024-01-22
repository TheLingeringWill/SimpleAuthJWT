import React, { forwardRef } from 'react';
import InputField from '@/lib/InputField';
import type InputAreaProps from './inputArea.props';

/**
 * A custom input area component that can contain an input field, label, and paragraph elements.
 *
 * @param {InputAreaProps} props - The props for the InputArea component.
 * @param {React.Ref<HTMLInputElement>} ref - Ref to the input field element.
 * @returns {JSX.Element} - The custom input area component.
 */
const InputArea = forwardRef<HTMLInputElement, InputAreaProps>(
  (
    { inputFieldProps, labelProps, paragraphProps, ...other }: InputAreaProps,
    ref,
  ): JSX.Element => {
    /**
     * Core component representing the structure of the InputArea.
     *
     * @returns {JSX.Element} - The core structure of the InputArea.
     */
    const Core = (): JSX.Element => (
      <>
        {labelProps && <label {...labelProps}>{labelProps?.children}</label>}
        <InputField
          ref={ref}
          {...inputFieldProps}
        />
        {paragraphProps && (
          <p {...paragraphProps}>{paragraphProps?.children}</p>
        )}
      </>
    );

    return (
      <>
        {Object.keys(other).length ? (
          <div {...other}>
            <Core />
          </div>
        ) : (
          <Core />
        )}
      </>
    );
  },
);

export default InputArea;
