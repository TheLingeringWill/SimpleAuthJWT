import api from '@/HttpClient';

async function confirm(id: string, token: string) {
  // We should normally check with cookies here !!!
  const res = await api.get(
    `auth/v1/auth/sign-up/confirm/${token}`,
    new Headers({
      'Authorization': `Bearer ${token}`,
    }),
  );
  return res.status === 202;
}

export default async function Page({
  params,
}: {
  params: {
    id: string;
    token: string;
  };
}) {
  const isConfirmed = await confirm(params.id, params.token);

  return (
    <div>
      {isConfirmed ? (
        <p>Your account has been registered </p>
      ) : (
        <p>
          Email Verification Failed. Email may be already verified or the link
          is broken.
        </p>
      )}
    </div>
  );
}
