/**
 * Props for a sign-up form component.
 *
 * @typedef {Object} SignUpFormProps
 * @property {string} firstName - The first name of the user.
 * @property {string} lastName - The last name of the user.
 * @property {string} email - The email address of the user.
 * @property {string} pseudo - The username or pseudonym of the user.
 * @property {string} phone - The phone number of the user.
 * @property {string} birth - The birthdate of the user.
 * @property {string} password - The user's password.
 * @property {string} verifPassword - The password verification field.
 */
type SignUpFormProps = {
  userType: number;
  firstName: string;
  lastName: string;
  email: string;
  pseudo: string;
  phone: string;
  birth: string;
  password: string;
  verifPassword: string;
};

export default SignUpFormProps;
