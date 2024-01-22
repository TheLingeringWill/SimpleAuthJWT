'use client';

import React, { useState } from 'react';

import { MuiOtpInput } from 'mui-one-time-password-input';
import api from '@/HttpClient';
//import Cookies from 'js-cookie';
import { useRouter } from 'next/navigation';
import type OtpInputProps from './otp.props';

const OtpInput = ({ email, id }: OtpInputProps): JSX.Element => {
  const [otp, setOtp] = useState<string>('');
  const { push } = useRouter();
  const [errorMessage, setErrorMessage] = useState<boolean>(false);
  const handleChange = (value: string) => {
    setOtp(value);
  };

  const handleComplete = async (value: string) => {
    console.log(email, id, value);
    const resp = await api.put(
      'auth/v1/auth/sign-in/confirm',
      JSON.stringify({ email: email, id: id, otp: value }),
    );
    if (resp.status === 200) {
      push('/connected');
    } else {
      setErrorMessage(true);
    }
  };

  return (
    <div className='flex h-screen flex-col items-center justify-center bg-black'>
      <h2 className='text-white'>
        An email has been sent ! Type the code please
      </h2>
      <MuiOtpInput
        TextFieldsProps={{
          InputProps: { sx: { border: '2px white solid', color: 'white' } },
        }}
        length={8}
        value={otp}
        onChange={handleChange}
        onComplete={handleComplete}
        style={{ maxWidth: '650px', borderColor: 'white' }}
      />
      {errorMessage && <p className='text-red-500'>The code is not correct</p>}
    </div>
  );
};

export default OtpInput;
