import "./index.scss";

import Button from "@Components/Button";
import Logo from "@Components/Logo";
import TextInput from "@Components/TextInput";
import * as ROUTES from "@Utils/routing";

interface Props {
  registration?: boolean;
}

function FormPage(props: Props) {
  const { registration } = props;

  const getLabel = () => (registration ? "Register" : "Sign In");

  const getLink = () => (registration ? ROUTES.LOGIN : ROUTES.REGISTRATION);

  const getAnchor = () => (registration ? "Already have an account" : "Dont't have an account");

  const redirect = () => history.pushState({}, "", ROUTES.TRACKS);

  return (
    <div className="form-page">
      <div className="form-page__background" />
      <form className="form-page__form">
        <Logo />
        <TextInput placeholder="Login" name="login" label="Login" />
        <TextInput placeholder="Password" name="password" label="Password" />
        {registration && (
          <TextInput
            placeholder="Confirm password"
            name="confirmPassword"
            label="Confirm password"
          />
        )}
        <div className="form__footer">
          <Button label={getLabel()} className="form__button" onClick={redirect} />
          <a className="form__link" href={getLink()}>
            {getAnchor()}
          </a>
        </div>
      </form>
    </div>
  );
}

export default FormPage;
