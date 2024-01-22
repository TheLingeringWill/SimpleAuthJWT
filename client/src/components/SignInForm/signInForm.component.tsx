'use client';

import type { FieldValues } from 'react-hook-form';
import React, { useState } from 'react';
import Link from 'next/link';
import api from '@/HttpClient';
import InputArea from '@/lib/InputArea';
import Form from '@/lib/Form';
import List from '@/lib/List';
import OtpInput, { OtpInputProps } from '@/components/OtpInput';
import SignInFormFields from './signInForm.fields';
import type SignInFormProps from './signInForm.props';

/**
 * A sign-in form component for user authentication.
 *
 * @returns {JSX.Element} - The Sign-In Form component.
 */
const SignInForm = (): JSX.Element => {
  const [emailSent, setEmailSent] = useState<boolean>(false);
  const [formData, setFormData] = useState<OtpInputProps>({} as OtpInputProps);

  const ButtonSignIn = (): JSX.Element => (
    <div className='flex flex-col items-center justify-center gap-4'>
      <Link
        className='hover:text-blue-500'
        href='/'
      >
        Go to sign-up ?
      </Link>
      <button
        className='bg-famy-gradient-color w-fit rounded-full border-solid px-6 py-4 font-[arial] font-bold'
        type='submit'
      >
        Sign-in
      </button>
    </div>
  );

  const handleSubmit = async (data: FieldValues) => {
    console.log(data);
    const resp = await api.put('auth/v1/auth/sign-in', JSON.stringify(data));
    const statusResp = resp.status;
    if (statusResp === 202) {
      setEmailSent(true);
      setFormData({
        email: resp.message.account.email,
        id: resp.message.account.id,
      });
    }
  };

  return (
    <>
      {emailSent ? (
        <OtpInput {...formData} />
      ) : (
        <Form<SignInFormProps>
          onSubmit={(data) => handleSubmit(data)}
          formProps={{
            className: 'm-8 flex flex-col w-3/5 gap-1 md:w-1/4',
          }}
        >
          {({ register, formState: { errors } }) => (
            <>
              <List
                items={SignInFormFields}
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
              <ButtonSignIn />
            </>
          )}
        </Form>
      )}
    </>
  );
};

export default SignInForm;
