import type { InputFieldProps } from '@/lib/InputField';

/**
 * Represents the properties for an InputArea component.
 *
 * @interface InputAreaProps
 * @extends React.HTMLAttributes<HTMLDivElement>
 */
export default interface InputAreaProps
  extends React.HTMLAttributes<HTMLDivElement> {
  /**
   * Properties for the input field within the InputArea component.
   *
   * @type {InputFieldProps}
   */
  inputFieldProps: InputFieldProps;

  /**
   * Optional properties for a label element within the InputArea component.
   *
   * @type {React.LabelHTMLAttributes<HTMLLabelElement>}
   */
  labelProps?: React.LabelHTMLAttributes<HTMLLabelElement>;

  /**
   * Optional properties for a paragraph element within the InputArea component.
   *
   * @type {React.HTMLAttributes<HTMLParagraphElement>}
   */
  paragraphProps?: React.HTMLAttributes<HTMLParagraphElement>;
}
