import "./index.scss";

type DefaultInputProps = {
  placeholder?: string;
};

interface FormInputProps extends DefaultInputProps {
  label?: string;
  name: string;
}

function TextInput(props: DefaultInputProps | FormInputProps) {
  const { label, name } = props as FormInputProps;

  const formInputProps = { ...props, className: "text-input", type: "text" };

  const defaultInputProps = { ...props, className: "text-input", type: "text" };

  return name || label ? (
    <div className="input-container">
      <label className="input-label" htmlFor={name}>
        {label}
      </label>
      <input {...formInputProps} />
    </div>
  ) : (
    <input {...defaultInputProps} />
  );
}

export default TextInput;
