DROP TABLE IF EXISTS auth;

CREATE TABLE auth (
  /* ID fields */
  id BIGINT,
  /* Mandatory fields */
  verify_token TEXT, -- JWT token sent to user to verify his authenticity
  /* Optional fields */
  refresh_token TEXT NULL, -- JWT token stocked on cookies for credentials
  otp TEXT NULL, -- One Time Password sent to user to verify his authenticity
  /* Primary keys constraints */
  CONSTRAINT auth_pkey PRIMARY KEY (id)
/* Foreign keys constraints */
    /* Unique constraints */
);


/* For one-to-one relation ship */
