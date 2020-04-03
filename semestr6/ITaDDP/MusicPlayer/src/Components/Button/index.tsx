import "./index.scss";

import cx from "classnames";

interface Props {
  label: string;
  className?: string;
  onClick?: () => void;
}

function Button(props: Props) {
  const { label, className, onClick } = props;

  const classes = cx("button", { [className as string]: className });

  return (
    <button className={classes} onClick={onClick}>
      {label}
    </button>
  );
}

export default Button;
