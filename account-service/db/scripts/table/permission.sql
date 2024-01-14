DROP TABLE IF EXISTS permission;

CREATE TABLE permission
(
  /* ID fields */
  id BIGSERIAL,

  /* Mandatory fields */
  description VARCHAR(200) NOT NULL,

  /* Optional fields */

    /* Primary keys constraints */
  CONSTRAINT permission_pkey PRIMARY KEY (id)

/* Foreign keys constraints */

    /* Uniques constraints */
);

/* For one-to-one relation ship constraints */
