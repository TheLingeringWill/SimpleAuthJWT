DROP TABLE IF EXISTS account;

CREATE TABLE account
(
  /* ID fields */
  id BIGSERIAL,
  uuid UUID NOT NULL DEFAULT UUID_GENERATE_V4(),
  role_id BIGINT,

  /* Mandatory fields */
  first_name VARCHAR(50) NOT NULL,
  last_name VARCHAR(50) NOT NULL,
  email VARCHAR(50) NOT NULL,
  password VARCHAR(32) NOT NULL,
  is_verified BOOLEAN NOT NULL DEFAULT FALSE,

  /* Optional fields */
  address VARCHAR(36) NULL, -- will be mandotary in the future

  /* Primary keys constraints */
  CONSTRAINT account_pkey PRIMARY KEY (id),

  /* Foreign keys constraints */
  CONSTRAINT account_role_fkey FOREIGN KEY (role_id)
  REFERENCES role (id),

  /* Uniques constraints */
  CONSTRAINT account_email_key UNIQUE (email)
);

/* For one-to-one relation ship constraints */
