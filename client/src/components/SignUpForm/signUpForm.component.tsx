'use client';

import type { FieldValues } from 'react-hook-form';
import React, { useState } from 'react';
import Link from 'next/link';
import Cookies from 'js-cookie';
import InputArea from '@/lib/InputArea';
import Form from '@/lib/Form';
import List from '@/lib/List';
import api from '@/HttpClient';
import SignUpFormFields from './signUpForm.fields';
import type SignUpFormProps from './signUpForm.props';

/**
 * A sign-up form component for user registration.
 *
 * @returns {JSX.Element} - The Sign-Up Form component.
 */
const SignUpForm = (): JSX.Element => {
  const [emailSent, setEmailSent] = useState<boolean>(false);

  const ButtonSignUp = (): JSX.Element => (
    <div className='flex flex-col items-center justify-center gap-4'>
      <Link
        className='hover:text-blue-500'
        href='/sign-in'
      >
        Go to sign-in ?
      </Link>
      <button
        className='bg-famy-gradient-color w-fit rounded-full border-solid px-6 py-4 font-[arial] font-bold'
        type='submit'
      >
        Sign-up
      </button>
    </div>
  );

  const handleSubmit = async (data: FieldValues) => {
    console.log(data);
    const req: Record<string, string | number> = {
      first_name: data.firstName,
      last_name: data.lastName,
      email: data.email,
      password: data.password,
      role_id: data.userType,
    };
    const resp = await api.post('auth/v1/auth/sign-up', JSON.stringify(req));
    const statusResp = resp.status;
    console.log(resp.message.auth.verify_token);
    if (statusResp === 201 || statusResp === 202) {
      setEmailSent(true);
      Cookies.set('verify_token', resp.message.auth.verify_token, {
        sameSite: 'None',
      });
      Cookies.set('id', resp.message.auth.id, { sameSite: 'None' });
    }
  };

  return (
    <Form<SignUpFormProps>
      defaultValues={{
        defaultValues: {
          userType: 1,
        },
      }}
      onSubmit={handleSubmit}
      formProps={{
        className: 'flex flex-col w-3/5 gap-1 md:w-1/4',
      }}
    >
      {({ register, formState: { errors } }) => (
        <>
          <div
            className='m-4 flex items-center justify-center'
            {...register('userType')}
          ></div>
          <List
            items={SignUpFormFields}
            renderItem={(item, index) => (
              <React.Fragment key={index}>
                <InputArea
                  inputFieldProps={{
                    className:
                      'flex flex-row items-center rounded-full py-2 px-3 gap-2 bg-origin-padding border-solid border-2 outline-white border-white',
                    inputProps: {
                      className: 'w-[90%] bg-black outline-0',
                      type: item.type,
                      placeholder: item.placeholder,
                      ...register(item.name, item.registerOpt),
                    },
                    imageProps: {
                      className: 'max-w-5 max-h-5',
                      src: item.srcImage,
                      alt: item.srcImage,
                    },
                  }}
                  paragraphProps={{
                    className: `w-max ${
                      item.name in errors ? 'visible' : 'invisible'
                    } px-2 text-red-500`,
                    children: item.name in errors ? item.errorMessage : '_',
                  }}
                />
              </React.Fragment>
            )}
          />
          <ButtonSignUp />
          {emailSent && <p>Email has been sent !</p>}
        </>
      )}
    </Form>
  );
};

export default SignUpForm;
