DROP TABLE IF EXISTS provider;

CREATE TABLE provider
(
  /* ID fields */
  id BIGSERIAL,

  /* Mandatory fields */
  name VARCHAR(50),	-- Name of the provider
  wsep VARCHAR(200),	-- Web Service endpoint from provider

  /* Optional fields */

  /* Primary keys constraints */
  CONSTRAINT provider_pkey PRIMARY KEY (id)

/* Foreign keys constraints */

    /* Unique constraints */
);

/* For one-to-one relation ship */
