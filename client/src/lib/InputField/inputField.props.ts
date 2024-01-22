/**
 * Represents the properties for an InputField component.
 *
 * @interface InputFieldProps
 * @extends React.HTMLAttributes<HTMLDivElement>
 */
export default interface InputFieldProps
  extends React.HTMLAttributes<HTMLDivElement> {
  /**
   * Properties for the input element within the InputField component.
   *
   * @type {React.InputHTMLAttributes<HTMLInputElement>}
   */
  inputProps: React.InputHTMLAttributes<HTMLInputElement>;

  /**
   * Optional properties for an image element within the InputField component.
   *
   * @type {React.ImgHTMLAttributes<HTMLImageElement>}
   */
  imageProps?: React.ImgHTMLAttributes<HTMLImageElement>;
}
