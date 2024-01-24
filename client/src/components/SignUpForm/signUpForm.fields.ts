import type InputFormAuthProps from '@/components/InputFormAuth';
import type SignUpFormProps from './signUpForm.props';

import api from '@/HttpClient';

const SignUpFormFields: InputFormAuthProps<
  Omit<SignUpFormProps, 'userType'>
>[] = [
  {
    type: 'text',
    name: 'firstName',
    registerOpt: {},
    placeholder: 'First name',
    srcImage: '/icons/account.svg',
    errorMessage: '',
  },
  {
    type: 'text',
    name: 'lastName',
    registerOpt: {},
    placeholder: 'Last name',
    srcImage: '/icons/account.svg',
    errorMessage: '',
  },
  {
    type: 'email',
    name: 'email',
    registerOpt: {
      required: true,
      pattern: /^[^\s@]+@[^\s@]+\.[^\s@]+$/,
      validate: async (value: string) =>
        (
          await api.post(
            'account/v1/account/verify',
            new URLSearchParams({ 'email': value }),
            new Headers({
              'Content-Type': 'application/x-www-form-urlencoded',
            }),
          )
        ).status === 404,
    },
    placeholder: 'Email',
    srcImage: '/icons/mail.svg',
    errorMessage: 'Email is not valid',
  },
  {
    type: 'phone',
    name: 'phone',
    registerOpt: {
      required: true,
      pattern:
        /^(?:(?:(?:[0-9]{2}\.){4}[0-9]{2}|(?:[0-9]{2}\.){2}[0-9]{2})|(?:(?:[0-9]{3}\.){3}[0-9]{2}|(?:[0-9]{3}\.){2}[0-9]{2}|(?:[0-9]{4}\.){2}[0-9]{2}|[0-9]{10}))$/,
    },
    placeholder: 'Phone number',
    srcImage: '/icons/phone.svg',
    errorMessage: 'The phone number is not correct',
  },
  {
    type: 'text',
    name: 'pseudo',
    registerOpt: { },
    placeholder: 'Pseudo',
    srcImage: '/icons/account.svg',
    errorMessage: 'Pseudo already exists',
  },
  {
    type: 'password',
    name: 'password',
    registerOpt: {
      required: true,
      pattern: /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[!@#$%^&*]).{8,}$/,
    },
    placeholder: 'Password',
    srcImage: '/icons/key.svg',
    errorMessage: 'The password is invalid',
  },
];

export default SignUpFormFields;
