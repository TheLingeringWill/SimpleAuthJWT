DROP TABLE IF EXISTS role;

CREATE TABLE role
(
  /* ID fields */
  id BIGSERIAL,

  /* Mandatory fields */
  description VARCHAR(200) NOT NULL,

  /* Optional fields */

    /* Primary keys constraints */
  CONSTRAINT role_pkey PRIMARY KEY (id)

/* Foreign keys constraints */

    /* Uniques constraints */
);

/* For one-to-one relation ship constraints */
